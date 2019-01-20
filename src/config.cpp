/*
 * config.cpp
 *
 *  Created on: 20 Jan 2019
 *      Author: Gabi
 */

Config::Config()
{
    this->hostname = "";
}

void Config::setHostname(STRINGCLASS hostname)
{
    this->hostname = hostname;
}

STRINGCLASS Config::getHostname()
{
    return this->hostname;
}
