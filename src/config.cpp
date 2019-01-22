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

void Config::setApiUrl(STRINGCLASS url)
{
    this->apiUrl = url;
}

STRINGCLASS Config::getApiUrl()
{
    return this->apiUrl;
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

int Config::saveConfig()
{
    std::ofstream FileOut(CONFIG_FILE_NAME);

    // cehck if the file is opened
    if (! FileOut.good()) {
        return 0;
    }

    // save config for hostname
    FileOut << this->prepareForSave("hostname", this->getHostname());

    // save the ip address
    FileOut << this->prepareForSave("ip_address", this->getIpAddress());

    // save the application path
    FileOut << this->prepareForSave("path", this->getPath());

    // save the API URL
    FileOut << this->prepareForSave("api_url", this->getApiUrl());

    return 1;
}

int Config::loadConfig()
{
    std::ifstream FileIn(CONFIG_FILE_NAME);
    STRINGCLASS line;

    // check if file is opened
    if (! FileIn.good()) {
        return 0;
    }

    // read host
    if (! (FileIn >> line)) {
        return 0;
    }
    line.erase(0, 9);
    this->setHostname(line);

    // read ip address
    if (! (FileIn >> line)) {
        return 0;
    }
    line.erase(0, 11);
    this->setIpAddress(line);

    // read application path
    if (! (FileIn >> line)) {
        return 0;
    }
    line.erase(0, 5);
    this->setPath(line);

    // read the API URL
    if (! (FileIn >> line)) {
        return 0;
    }
    line.erase(0, 8);
    this->setApiUrl(line);

    return 1;
}
