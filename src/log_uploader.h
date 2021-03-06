/*
 * log_uploader.h
 *
 *  Created on: 2 Feb 2019
 *      Author: Gabi
 */

#ifndef SRC_LOG_UPLOADER_H_
#define SRC_LOG_UPLOADER_H_

#include <curl/curl.h>

class LogUploader
{
private:
    class Display Display;

    unsigned int logChunkSize;

    STRINGCLASS onlyLog;                                // if defined, only this log will be processed

    /**
     * Build the POST body string
     */
    STRINGCLASS buildPost( LogItem, STRINGCLASS& );

    /**
     * Handle upload errors
     */
    void uploadError( CURL*, STRINGCLASS*, long );

public:
    /*
     * Default Constructor
     */
    LogUploader();

    /**
     * Getter and Setter for Only Log
     */
    void setOnlyLog( STRINGCLASS );
    STRINGCLASS getOnlyLog();

    /**
     * Cycle through the logs and call the parser
     */
    void Cycle();

    /*
     * Log Parse - read lines from log
     */
    int LogParser( LogItem& );

    /**
     * Read contents from the file and return the number of lines read
     */
    int LogReader( std::ifstream*, STRINGCLASS & );

    /**
     * Skip a number of lines in the log file before starting to read
     */
    void SkipLines( std::ifstream*, LogItem );

    /*
     * Upload the loaded lines to the DB
     */
    int Upload( LogItem, STRINGCLASS& );
};

#include <sstream>
#include <sys/stat.h>

#include "log_uploader.cpp"

#endif /* SRC_LOG_UPLOADER_H_ */
