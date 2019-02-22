/*
 * log_config.cpp
 *
 *  Created on: 23 Jan 2019
 *      Author: Gabi
 */

LogConfig::LogConfig()
{
    class Display disp;

    this->Display = disp;
}

int LogConfig::loadConfig()
{
    PXMLELEMENT type, subtype, pathitem;
    STRINGCLASS logConfigFile;

    if ( Config.getLogConfigFileName().length() != 0 ) {
        logConfigFile = Config.getLogConfigFileName();
    } else {
        logConfigFile = LOG_CONFIG_FILE_NAME;
    }

    // check if file exists
    FILE *fis = fopen( logConfigFile.c_str(), "r" );
    if ( ! fis ) {
        this->Display.DisplayError( "Log config file is missing !!! Exiting." );
        return 0;
    }
    fclose( fis );

    TiXmlDocument xml( LOG_CONFIG_FILE_NAME );
    xml.LoadFile();

    // check first element
    PXMLELEMENT root = xml.FirstChildElement();
    if ( ! root ) {
        this->Display.DisplayError( "Error reading root element of xml! Exiting" );
        return 0;
    }
    if ( strcmp("log", root->Value()) != 0 ) {
        this->Display.DisplayError( "XML is not correct! Exiting" );
        return 0;
    }

    // parse the log xml
    type = root->FirstChildElement();
    if ( ! type ) {
        this->Display.DisplayError( "Error reading First Child element of xml! Exiting" );
        return 0;
    }

    while ( type ) {
        subtype = type->FirstChildElement();
        if ( ! subtype ) {
            continue;
        }

        // subtypes
        while ( subtype ) {
            pathitem = subtype->FirstChildElement();
            if ( ! pathitem ) {
                continue;
            }

            // items
            while ( pathitem ) {
                LogItems.CreateItem( type->Value(), subtype->Value(), pathitem->GetText() );

                pathitem = pathitem->NextSiblingElement();
            }

            subtype = subtype->NextSiblingElement();
        }

        type = type->NextSiblingElement();
    }

    return 1;
}
