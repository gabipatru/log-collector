/*
 * config.h
 *
 *  Created on: 20 Jan 2019
 *      Author: Gabi
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

class Config
{
private:
    STRINGCLASS hostname;
    STRINGCLASS ipAddress;

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
};

#include "constant.h"
#include "config.cpp"

/**
 * Config is a global variable
 */
class Config Config;

#endif /* SRC_CONFIG_H_ */
