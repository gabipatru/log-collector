/*
 * log_config.h
 *
 *  Created on: 23 Jan 2019
 *      Author: Gabi
 */

#ifndef SRC_LOG_CONFIG_H_
#define SRC_LOG_CONFIG_H_

#define LOG_CONFIG_FILE_NAME "log.conf"

class LogConfig
{
public:
    /**
     * Save config to file and load config from file
     */
    int saveConfig();
    int loadConfig();
};

#include "lib/tinyxml/tinyxml.cpp"
#include "lib/tinyxml/tinyxmlerror.cpp"
#include "lib/tinyxml/tinyxmlparser.cpp"
#include "lib/tinyxml/tinystr.cpp"

typedef TiXmlElement* PXMLELEMENT;

#include "log_item.h"

#include "log_config.cpp"

#endif /* SRC_LOG_CONFIG_H_ */
