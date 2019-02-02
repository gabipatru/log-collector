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
    STRINGCLASS pBuffer[MAX_LINES_READ];
    STRINGCLASS line;
    std::ifstream file( Item.getPath().c_str() );
    int i;
    unsigned long bytesRead = 0;

    if ( ! Item.Validate() ) {
        return 0;
    }

    // check if the log file actually exists
    if ( ! file ) {
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

        pBuffer[i] = line;

        i++;
        // stop if the limit number of lines was reached
        if ( i >= MAX_LINES_READ ) {
            break;
        }
    }

    file.close();

    return 1;
}
