/*
 * config.cpp
 *
 *  Created on: 20 Jan 2019
 *      Author: Gabi
 */

Config::Config()
{
    this->hostname = "";
    this->ipAddress = "";
}

void Config::setHostname(STRINGCLASS hostname)
{
    this->hostname = hostname;
}

STRINGCLASS Config::getHostname()
{
    return this->hostname;
}

void Config::setIpAddress(STRINGCLASS ipAddress)
{
    this->ipAddress = ipAddress;
}

STRINGCLASS Config::getIpAddress()
{
    return this->ipAddress;
}

void Config::setPath(STRINGCLASS path)
{
    this->path = path;
}

STRINGCLASS Config::getPath()
{
    return this->path;
}
