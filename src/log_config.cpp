/*
 * log_config.cpp
 *
 *  Created on: 23 Jan 2019
 *      Author: Gabi
 */

int LogConfig::loadConfig()
{
    PXMLELEMENT type, subtype, pathitem;

    // check if file exists
    FILE *fis = fopen( LOG_CONFIG_FILE_NAME, "r" );
    if ( ! fis ) {
        printf( "Log config file is missing !!!\n" );
        return 0;
    }
    fclose( fis );

    TiXmlDocument xml( LOG_CONFIG_FILE_NAME );
    xml.LoadFile();

    // check first element
    PXMLELEMENT root = xml.FirstChildElement();
    if ( ! root ) {
        return 0;
    }
    if ( strcmp("log", root->Value()) != 0 ) {
        return 0;
    }

    // parse the log xml
    type = root->FirstChildElement();
    if ( ! type ) {
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
