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
    STRINGCLASS hostname;
    STRINGCLASS ipAddress;
    STRINGCLASS path;

    /**
     * Prepare a config to be saved in the file
     */
    STRINGCLASS prepareForSave(STRINGCLASS, STRINGCLASS);

public:
    Config();

    /**
     * Getter and Setter for Hostname
     */
    void setHostname(STRINGCLASS);
    STRINGCLASS getHostname();

    /**
     * Getter and Setter for IP Address
     */
    void setIpAddress(STRINGCLASS);
    STRINGCLASS getIpAddress();

    /**
     * Getter and Setter for Path
     */
    void setPath(STRINGCLASS);
    STRINGCLASS getPath();

    /**
     * Save config to file and load config from file
     */
    void saveConfig();
    void loadConfig();
};

#include "constant.h"
#include "config.cpp"

/**
 * Config is a global variable
 */
class Config Config;

#endif /* SRC_CONFIG_H_ */
