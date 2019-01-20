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

public:
    Config();

    void setHostname(STRINGCLASS);
    STRINGCLASS getHostname();
};

#include "constant.h"
#include "config.cpp"

/**
 * Config is a global variable
 */
class Config conf;

#endif /* SRC_CONFIG_H_ */
