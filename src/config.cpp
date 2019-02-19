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
    this->path = "";
    this->apiUrl = "";
    this->logChunkSize = LOG_CHUNK_SIZE;
    this->uploadDelay = UPLOAD_DELAY;
    this->uploadIterations = UPLOAD_ITERATIONS;
}

void Config::setHostname( STRINGCLASS hostname )
{
    this->hostname = hostname;
}

STRINGCLASS Config::getHostname()
{
    return this->hostname;
}

void Config::setIpAddress( STRINGCLASS ipAddress )
{
    this->ipAddress = ipAddress;
}

STRINGCLASS Config::getIpAddress()
{
    return this->ipAddress;
}

void Config::setPath( STRINGCLASS path )
{
    this->path = path;
}

STRINGCLASS Config::getPath()
{
    return this->path;
}

void Config::setApiUrl( STRINGCLASS url )
{
    this->apiUrl = url;
}

STRINGCLASS Config::getApiUrl()
{
    return this->apiUrl;
}

void Config::setLogChunkSize( unsigned int size )
{
    this->logChunkSize = size;
}

unsigned int Config::getLogChunkSize()
{
    return this->logChunkSize;
}

void Config::setUploadDelay( unsigned int delay )
{
    this->uploadDelay = delay;
}

unsigned int Config::getUploadDelay()
{
    return this->uploadDelay;
}

void Config::setUploadIterations( unsigned int nr )
{
    this->uploadIterations = nr;
}

unsigned int Config::getUploadIterations()
{
    return this->uploadIterations;
}

STRINGCLASS Config::prepareForSave( STRINGCLASS configName, STRINGCLASS configValue )
{
    STRINGCLASS buffer;

    buffer = configName + "=" + configValue;
    if ( buffer.find( "\n" ) == -1 ) {
        buffer = buffer + "\n";
    }

    return buffer;
}

int Config::saveConfig()
{
    char buffer[30];

    // remove old file
    remove( CONFIG_FILE_NAME );

    std::ofstream FileOut( CONFIG_FILE_NAME );

    // cehck if the file is opened
    if ( ! FileOut.good() ) {
        return 0;
    }

    // save config for hostname
    FileOut << this->prepareForSave( "hostname", this->getHostname() );

    // save the ip address
    FileOut << this->prepareForSave( "ip_address", this->getIpAddress() );

    // save the application path
    FileOut << this->prepareForSave( "path", this->getPath() );

    // save the API URL
    FileOut << this->prepareForSave( "api_url", this->getApiUrl() );

    // save the Log Chunk Size
    snprintf( buffer, sizeof( buffer ), "%u", this->getLogChunkSize() );
    FileOut << this->prepareForSave( "log_chunk_size", buffer );

    // save the Upload Delay
    snprintf( buffer, sizeof( buffer ), "%u", this->getUploadDelay() );
    FileOut << this->prepareForSave( "upload_delay", buffer );

    // save the Upload Iterations
    snprintf( buffer, sizeof( buffer ), "%u", this->getUploadIterations() );
    FileOut << this->prepareForSave( "upload_iterations", buffer );

    FileOut.close();

    return 1;
}

int Config::loadConfig()
{
    unsigned int buffer;
    char *ptr;
    std::ifstream FileIn( CONFIG_FILE_NAME );
    STRINGCLASS line;

    // check if file is opened
    if ( ! FileIn.good() ) {
        return 0;
    }

    // read host
    if ( ! ( FileIn >> line ) ) {
        return 0;
    }
    line.erase( 0, 9 );
    this->setHostname( line );

    // read ip address
    if ( ! ( FileIn >> line ) ) {
        return 0;
    }
    line.erase( 0, 11 );
    this->setIpAddress( line );

    // read application path
    if ( ! ( FileIn >> line ) ) {
        return 0;
    }
    line.erase( 0, 5 );
    this->setPath( line );

    // read the API URL
    if ( ! ( FileIn >> line ) ) {
        return 0;
    }
    line.erase( 0, 8 );
    this->setApiUrl( line );

    // read the Log Chunk Size
    if ( ! ( FileIn >> line ) ) {
        return 0;
    }
    line.erase( 0, 15 );
    buffer = (int) strtoul( line.c_str(), &ptr, 10 );
    this->setLogChunkSize( buffer );

    // read the Upload Delay
    if ( ! ( FileIn >> line ) ) {
        return 0;
    }
    line.erase( 0, 13 );
    buffer = (int) strtoul( line.c_str(), &ptr, 10 );
    this->setUploadDelay( buffer );

    // read the Upload Iterations
    if ( ! ( FileIn >> line ) ) {
        return 0;
    }
    line.erase( 0, 18 );
    buffer = (int) strtoul( line.c_str(), &ptr, 10 );
    this->setUploadIterations( buffer );

    return 1;
}
