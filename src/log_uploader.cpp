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
    int result;
    class LogItem Item;
    class LogConfig LogConfig;

    LogItems.Reset();

    Item = LogItems.getCurrentItemAndInc();

    while( Item == true ) {
        // check if we must process this log
        if (this->getOnlyLog().length() > 0 && this->getOnlyLog().compare( Item.getPath() ) != 0) {
            Item = LogItems.getCurrentItemAndInc();
            continue;
        }

        result = this->LogParser( Item );
        LogConfig.updateXML( Item );
        if ( result = 0 ) {
            return;
        }

        Item = LogItems.getCurrentItemAndInc();
    }
}

int LogUploader::LogParser( LogItem& Item )
{
    char msgBuffer[200];
    STRINGCLASS buffer("");
    std::ifstream file( Item.getPath().c_str() );
    unsigned long int linesRead = 0, linesUploaded = 0;
    int result;
    double maxRunTime = (double) Config.getApplicationRuntime();

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

    snprintf( msgBuffer, sizeof( msgBuffer ), "Start processing %s", Item.getPath().c_str() );
    this->Display.Info( msgBuffer );

    // read from log
    while ( ! file.eof() ) {
        // if the maxtime is reached, end parsing
        if ( maxRunTime < Application.MeasureRunTime() ) {
            Item.setLine( linesUploaded );
            this->Display.Warning( "Maximum execution time exceded. Stopping" );
            return 0;
        }

        // read data from log only if we have to
        if (buffer.length() == 0) {
            linesRead = this->LogReader( &file, buffer );
        }

        // upload data
        result = this->Upload( Item, buffer );
        if ( ! result ) {
            Application.Sleep();
            // if the upload failed, we must try uploading the same data again
            continue;
        }

        // reset data
        buffer = "";
        linesUploaded = linesUploaded + linesRead;

        // if the maxtime is reached, end parsing
        if ( maxRunTime < Application.MeasureRunTime() ) {
            Item.setLine( linesUploaded );
            this->Display.Warning( "Maximum execution time exceded. Stopping" );
            return 0;
        }

        Application.Sleep();
    }

    file.close();
    Item.setLine( linesUploaded );

    return 1;
}

int LogUploader::LogReader( std::ifstream *file, STRINGCLASS &buffer )
{
    STRINGCLASS line;
    unsigned long bytesRead = 0, linesRead = 0;

    while ( ! file->eof() ) {
        std::getline( *file, line );

        buffer += line;
        buffer += "\n";

        linesRead++;

        // calculate new value of bytes read
        bytesRead = bytesRead + line.length();
        if ( bytesRead >= Config.getLogChunkSize() ) {
            return linesRead;
        }
    }

    return linesRead;
}

int LogUploader::Upload( LogItem Item, STRINGCLASS& buffer )
{
    CURL *curl;
    CURLcode response;
    STRINGCLASS PostFields( "" );
    char msgBuffer[200];
    long httpCode;
    double uploadTime;

    if ( ! Item.Validate() ) {
        return 0;
    }

    curl_global_init( CURL_GLOBAL_ALL );
    curl = curl_easy_init();

    if ( curl ) {
        Application.MarkUploadStart();

        // POST URL
        curl_easy_setopt( curl, CURLOPT_URL, Config.getApiUrl().c_str() );

        // set up post fields
        PostFields = this->buildPost( Item, buffer );

        // add POST Fields
        curl_easy_setopt( curl, CURLOPT_POSTFIELDS, PostFields.c_str() );

        // make request, get response code
        response = curl_easy_perform( curl );
        if ( response != CURLE_OK ) {
            this->uploadError( curl, &buffer, response );
            return 0;
        }

        // check status code
        curl_easy_getinfo ( curl, CURLINFO_RESPONSE_CODE, &httpCode );
        if ( httpCode != 200 ) {
            this->uploadError( curl, &buffer, httpCode );
            return 0;
        }

        uploadTime = Application.MeasureUploadTime();

        // display successful upload message
        snprintf(
                msgBuffer, sizeof( msgBuffer ),
                "Uploaded %s%d%s bytes in %s%7.3f%s ms",
                LINUX_TERMINAL_WHITE, buffer.length(), LINUX_TERMINAL_NOCOLOR,
                LINUX_TERMINAL_WHITE, uploadTime, LINUX_TERMINAL_NOCOLOR
        );
        this->Display.DisplayMessage( msgBuffer );

        curl_easy_cleanup( curl );
    }

    curl_global_cleanup();

    return 1;
}

void LogUploader::uploadError( CURL* curl, STRINGCLASS* buffer, long code )
{
    char msgBuffer[200];

    printf( "\nError while performing HTTP request. Response code: %d \n", code );

    curl_easy_cleanup( curl );
    curl_global_cleanup();

    snprintf(
            msgBuffer, sizeof( msgBuffer ),
            "Failed to upload %s%d%s bytes",
            LINUX_TERMINAL_WHITE, buffer->length(), LINUX_TERMINAL_NOCOLOR
    );
    this->Display.DisplayError( msgBuffer );
}

STRINGCLASS LogUploader::buildPost( LogItem Item, STRINGCLASS& buffer )
{
    STRINGCLASS PostFields;

    PostFields = PostFields + "type=" + Item.getType().c_str();
    PostFields = PostFields + "&subType=" + Item.getSubType().c_str();
    PostFields = PostFields + "&hostname=" + Config.getHostname().c_str();
    PostFields = PostFields + "&ip_address=" + Config.getIpAddress().c_str();
    PostFields = PostFields + "&client=" + Config.getClient().c_str();
    PostFields = PostFields + "&payload=" + buffer.c_str();

    return PostFields;
}
