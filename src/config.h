/*
 * config.h
 *
 *  Created on: 20 Jan 2019
 *      Author: Gabi
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

#define CONFIG_FILE_NAME "config.conf"

class Config
{
private:
    class Display Display;

    STRINGCLASS hostname;
    STRINGCLASS ipAddress;
    STRINGCLASS path;
    STRINGCLASS apiUrl;
    STRINGCLASS logConfigFileName;
    STRINGCLASS client;

    unsigned int logChunkSize;
    unsigned int uploadDelay;
    unsigned int applicationRuntime;

    /**
     * Prepare a config to be saved in the file
     */
    STRINGCLASS prepareForSave( STRINGCLASS, STRINGCLASS );

public:
    Config();

    /**
     * Getter and Setter for Client
     */
    void setClient( STRINGCLASS );
    STRINGCLASS getClient();

    /**
     * Getter and Setter for Hostname
     */
    void setHostname( STRINGCLASS );
    STRINGCLASS getHostname();

    /**
     * Getter and Setter for IP Address
     */
    void setIpAddress( STRINGCLASS );
    STRINGCLASS getIpAddress();

    /**
     * Getter and Setter for Path
     */
    void setPath( STRINGCLASS );
    STRINGCLASS getPath();

    /**
     * Getter and Setter for API URL
     */
    void setApiUrl( STRINGCLASS );
    STRINGCLASS getApiUrl();

    /**
     * Getter and Setter for Log Chunk Size
     */
    void setLogChunkSize( unsigned int );
    unsigned int getLogChunkSize();

    /**
     * Getter and Setter for Upload Delay
     */
    void setUploadDelay( unsigned int );
    unsigned int getUploadDelay();

    /**
     * Getter and Setter for Application Runtime
     */
    void setApplicationRuntime( unsigned int );
    unsigned int getApplicationRuntime();

    /**
     * Getter and Setter for Log Config File Name
     */
    void setLogConfigFileName( STRINGCLASS );
    STRINGCLASS getLogConfigFileName();

    /**
     * Save config to file and load config from file
     */
    int saveConfig();
    int loadConfig();
};

#include "constant.h"
#include "config.cpp"

/**
 * Config is a global variable
 */
class Config Config;

#endif /* SRC_CONFIG_H_ */
