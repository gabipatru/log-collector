/*
 * log_uploader.cpp
 *
 *  Created on: 2 Feb 2019
 *      Author: Gabi
 */

LogUploader::LogUploader()
{
    this->logChunkSize = 32 * 1024;
}

int LogUploader::LogParser( LogItem Item )
{
    STRINGCLASS buffer;
    STRINGCLASS line;
    std::ifstream file( Item.getPath().c_str() );
    int i;
    unsigned long bytesRead = 0;

    if ( ! Item.Validate() ) {
        printf( "Item sent to logparser is not valid. Stopping logparser for this item !\n" );
        return 0;
    }

    // check if the log file actually exists
    if ( ! file ) {
        printf( "The Item's log file does not exist (%s)\n", Item.getPath().c_str() );
        return 0;
    }

    // read from log
    i = 0;
    while ( ! file.eof() ) {
        std::getline( file, line );

        // calculate new value of bytes read
        bytesRead = bytesRead + line.length();
        if ( bytesRead >= this->logChunkSize ) {
            break;
        }

        buffer += line;
        buffer += "\n";

        i++;
        // stop if the limit number of lines was reached
        if ( i >= MAX_LINES_READ ) {
            break;
        }
    }

    file.close();

    return this->Upload( Item, buffer );
}

int LogUploader::Upload( LogItem Item, STRINGCLASS& buffer )
{
    CURL *curl;
    CURLcode response;
    STRINGCLASS PostFields( "" );

    if ( ! Item.Validate() ) {
        return 0;
    }

    curl_global_init( CURL_GLOBAL_ALL );
    curl = curl_easy_init();

    if ( curl ) {
        // POST URL
        curl_easy_setopt( curl, CURLOPT_URL, Config.getApiUrl().c_str() );

        // set up post fields
        PostFields = this->buildPost( Item, buffer );

        // add POST Fields
        curl_easy_setopt( curl, CURLOPT_POSTFIELDS, PostFields.c_str() );

        // make request, get response code
        response = curl_easy_perform( curl );
        if ( response != CURLE_OK ) {
            printf( "\nError while performing HTTP request. Response code: %d \n", response );

            curl_easy_cleanup( curl );
            curl_global_cleanup();

            return 0;
        }

        curl_easy_cleanup( curl );
    }

    curl_global_cleanup();

    return 1;
}

STRINGCLASS LogUploader::buildPost( LogItem Item, STRINGCLASS& buffer )
{
    STRINGCLASS PostFields;

    PostFields = PostFields + "type=" + Item.getType().c_str();
    PostFields = PostFields + "&subType=" + Item.getSubType().c_str();
    PostFields = PostFields + "&hostname=" + Config.getHostname().c_str();
    PostFields = PostFields + "&ip_address=" + Config.getIpAddress().c_str();
    PostFields = PostFields + "&payload=" + buffer.c_str();

    return PostFields;
}
