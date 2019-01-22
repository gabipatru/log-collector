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

STRINGCLASS Config::prepareForSave(STRINGCLASS configName, STRINGCLASS configValue)
{
    STRINGCLASS buffer;

    buffer = configName + "=" + configValue;
    if (buffer.find("\n") == -1) {
        buffer = buffer + "\n";
    }

    return buffer;
}

void Config::saveConfig()
{
    std::ofstream FileOut(CONFIG_FILE_NAME);

    // save config for hostname
    FileOut << this->prepareForSave("hostname", this->hostname);

    // save the ip address
    FileOut << this->prepareForSave("ip_address", this->ipAddress);;

    // save the application path
    FileOut << this->prepareForSave("path", this->path);;;
}

void Config::loadConfig()
{

}
