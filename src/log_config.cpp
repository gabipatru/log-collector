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
    PXMLELEMENT type, subtype, item, path, line, createdAt, pathitem;
    STRINGCLASS logConfigFile;
    char* ptr;
    unsigned long int nrLines;

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
            item = subtype->FirstChildElement();
            if ( ! item ) {
                continue;
            }

            // items
            while ( item ) {
                path = item->FirstChildElement();
                if ( ! path ) {
                    continue;
                }
                line = path->NextSiblingElement();
                if ( ! line ) {
                    continue;
                }
                createdAt = line->NextSiblingElement();
                if ( ! createdAt ) {
                    continue;
                }

                nrLines = (long) strtoul( line->GetText(), &ptr, 10 );

                LogItems.CreateItem( type->Value(), subtype->Value(), path->GetText(), nrLines, createdAt->GetText() );

                item = item->NextSiblingElement();
            }

            subtype = subtype->NextSiblingElement();
        }

        type = type->NextSiblingElement();
    }

    return 1;
}
