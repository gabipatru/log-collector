/*
 * config.cpp
 *
 *  Created on: 20 Jan 2019
 *      Author: Gabi
 */

Config::Config()
{
    class Display disp;

    this->Display = disp;

    this->hostname = "";
    this->ipAddress = "";
    this->path = "";
    this->apiUrl = "";
    this->logChunkSize = LOG_CHUNK_SIZE;
    this->uploadDelay = UPLOAD_DELAY;
    this->applicationRuntime = MAX_RUNTIME;
    this->logConfigFileName = "";
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

void Config::setApplicationRuntime( unsigned int nr )
{
    this->applicationRuntime = nr;
}

unsigned int Config::getApplicationRuntime()
{
    return this->applicationRuntime;
}

void Config::setLogConfigFileName( STRINGCLASS name )
{
    this->logConfigFileName = name;
}

STRINGCLASS Config::getLogConfigFileName()
{
    return this->logConfigFileName;
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

    // check if the file is opened
    if ( ! FileOut.good() ) {
        this->Display.DisplayError( "Config file could not be created! Exiting." );
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
    snprintf( buffer, sizeof( buffer ), "%u", this->getApplicationRuntime() );
    FileOut << this->prepareForSave( "application_runtime", buffer );

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
        this->Display.DisplayError( "Config file not found! Exiting." );
        return 0;
    }

    // read host
    if ( ! ( FileIn >> line ) ) {
        this->Display.DisplayError( "Config for host not found! Exiting." );
        return 0;
    }
    line.erase( 0, 9 );
    this->setHostname( line );

    // read ip address
    if ( ! ( FileIn >> line ) ) {
        this->Display.DisplayError( "Config for ip address not found! Exiting." );
        return 0;
    }
    line.erase( 0, 11 );
    this->setIpAddress( line );

    // read application path
    if ( ! ( FileIn >> line ) ) {
        this->Display.DisplayError( "Config for application path not found! Exiting." );
        return 0;
    }
    line.erase( 0, 5 );
    this->setPath( line );

    // read the API URL
    if ( ! ( FileIn >> line ) ) {
        this->Display.DisplayError( "Config for API URL not found! Exiting." );
        return 0;
    }
    line.erase( 0, 8 );
    this->setApiUrl( line );

    // read the Log Chunk Size
    if ( ! ( FileIn >> line ) ) {
        this->Display.DisplayError( "Config for Log Chunk Size not found! Exiting." );
        return 0;
    }
    line.erase( 0, 15 );
    buffer = (int) strtoul( line.c_str(), &ptr, 10 );
    buffer = buffer * 1024;
    this->setLogChunkSize( buffer );

    // read the Upload Delay
    if ( ! ( FileIn >> line ) ) {
        this->Display.DisplayError( "Config for Upload Delay not found! Exiting." );
        return 0;
    }
    line.erase( 0, 13 );
    buffer = (int) strtoul( line.c_str(), &ptr, 10 );
    buffer = buffer * 1000;
    this->setUploadDelay( buffer );

    // read the Upload Iterations
    if ( ! ( FileIn >> line ) ) {
        this->Display.DisplayError( "Config for Upload Iterations not found! Exiting." );
        return 0;
    }
    line.erase( 0, 20 );
    buffer = (int) strtoul( line.c_str(), &ptr, 10 );
    this->setApplicationRuntime( buffer );

    return 1;
}
