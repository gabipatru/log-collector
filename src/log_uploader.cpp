/*
 * log_uploader.cpp
 *
 *  Created on: 2 Feb 2019
 *      Author: Gabi
 */

LogUploader::LogUploader()
{
    class Display disp;

    this->Display = disp;

    this->logChunkSize = 32 * 1024;
    this->onlyLog = "";
}

void LogUploader::setOnlyLog( STRINGCLASS only )
{
    this->onlyLog = only;
}

STRINGCLASS LogUploader::getOnlyLog()
{
    return this->onlyLog;
}

void LogUploader::Cycle()
{
    class LogItem Item;

    LogItems.Reset();

    Item = LogItems.getCurrentItemAndInc();

    while( Item == true ) {
        // check if we must process this log
        if (this->getOnlyLog().length() > 0 && this->getOnlyLog().compare( Item.getPath() ) != 0) {
            Item = LogItems.getCurrentItemAndInc();
            continue;
        }
        this->LogParser( Item );

        Item = LogItems.getCurrentItemAndInc();
    }
}

int LogUploader::LogParser( LogItem Item )
{
    char msgBuffer[200];
    STRINGCLASS buffer;
    std::ifstream file( Item.getPath().c_str() );
    int i;

    if ( ! Item.Validate() ) {
        this->Display.DisplayError( "Item sent to logparser is not valid. Stopping logparser for this item !" );
        return 0;
    }

    // check if the log file actually exists
    if ( ! file ) {
        snprintf( msgBuffer, sizeof( msgBuffer ), "The Item's log file does not exist (%s)", Item.getPath().c_str() );
        this->Display.DisplayError( msgBuffer );
        return 0;
    }

    // read from log
    i = 0;
    while ( ! file.eof() ) {
        // read data from log
        this->LogReader( &file, buffer );

        // upload data
        this->Upload( Item, buffer );

        // reset data
        buffer = "";

        i++;
        if ( i >= Config.getUploadIterations() ) {
            break;
        }

        usleep( Config.getUploadDelay() );
    }

    file.close();
}

void LogUploader::LogReader( std::ifstream *file, STRINGCLASS &buffer )
{
    STRINGCLASS line;
    unsigned long bytesRead = 0;

    while ( ! file->eof() ) {
        std::getline( *file, line );

        buffer += line;
        buffer += "\n";

        // calculate new value of bytes read
        bytesRead = bytesRead + line.length();
        if ( bytesRead >= Config.getLogChunkSize() ) {
            return;
        }
    }
}

int LogUploader::Upload( LogItem Item, STRINGCLASS& buffer )
{
    CURL *curl;
    CURLcode response;
    STRINGCLASS PostFields( "" );
    char msgBuffer[200];

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

            // display error message
            snprintf( msgBuffer, sizeof( msgBuffer ), "Failed to upload %s%d%s bytes", LINUX_TERMINAL_WHITE, buffer.length(), LINUX_TERMINAL_NOCOLOR );
            this->Display.DisplayError( msgBuffer );

            return 0;
        }

        // display successful upload message
        snprintf( msgBuffer, sizeof( msgBuffer ), "Uploaded %s%d%s bytes", LINUX_TERMINAL_WHITE, buffer.length(), LINUX_TERMINAL_NOCOLOR );
        this->Display.DisplayMessage( msgBuffer );

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
