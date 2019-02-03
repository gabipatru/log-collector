/*
 * log_uploader.h
 *
 *  Created on: 2 Feb 2019
 *      Author: Gabi
 */

#ifndef SRC_LOG_UPLOADER_H_
#define SRC_LOG_UPLOADER_H_

#define LOG_CHUNK_SIZE 32 // Size in KB
#define MAX_LINES_READ 10 // the maximum lines to be read from a file

class LogUploader
{
private:
    int logChunkSize;

    /**
     * Build the POST body string
     */
    STRINGCLASS buildPost(LogItem, STRINGCLASS&);

public:
    /*
     * Default Constructor
     */
    LogUploader();

    /*
     * Log Parse - read lines from log
     */
    int LogParser( LogItem );

    /*
     * Upload the loaded lines to the DB
     */
    int Upload( LogItem, STRINGCLASS& );
};

#include <sstream>
#include <curl/curl.h>

#include "log_uploader.cpp"

#endif /* SRC_LOG_UPLOADER_H_ */
