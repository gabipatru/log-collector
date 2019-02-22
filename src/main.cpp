/*
 * \<>
 *
 * main.cpp
 *
 *  Created on: 19 Jan 2019
 *      Author: Gabi
 *
 *  Main entry point to the program
 */

#include "main.h"

int main ( int argc, PCHAR argv[] )
{
    // vars
    int i, result;
    LogItem Item( "NULL", "NULL", "NULL" );

    STRINGCLASS argument;

    Setup Setup;
    Help Help;
    LogConfig LogConfig;
    LogUploader LogUploader;
    class Display Display;

    // check command line arguments
    for ( i=0; i<argc; i++ ) {
        argument = argv[i];

        // check if we need to run the setup
        if ( argument.compare( SETUP_ARGUMNET1 ) == 0 || argument.compare( SETUP_ARGUMENT2 ) == 0 ) {
            if ( i != 1 || argc > 2 ) {
                return LINUX_ERROR;
            }

            result = Setup.Start();
            if ( ! result ) {
                printf( "\nSomething went wrong during setup !!!\n" );
            }

            return LINUX_NO_ERROR;
        }

        // check if we have to display the help
        if ( argument.compare( HELP_ARGUMENT1 ) == 0 || argument.compare( HELP_ARGUMENT2 ) == 0 ) {
            Help.DisplayHelp();

            return LINUX_NO_ERROR;
        }

        // check if only one log has to be processed
        if ( argument.compare( ONLY_LOG_ARGUMENT1 ) == 0 || argument.compare( ONLY_LOG_ARGUMENT2 ) == 0 ) {
            // check if the next param exists
            if ( i+1 < argc ) {
                LogUploader.setOnlyLog( argv[i+1] );
            } else {
                Display.DisplayError( "Improper use of log parameter. Should be followed by log path" );
                return LINUX_ERROR;
            }
        }

        // check if a certain log config has to be loaded
        if ( argument.compare( CUSTOM_LOG_CONFIG_ARGUMENT1 ) == 0 || argument.compare( CUSTOM_LOG_CONFIG_ARGUMENT2 ) == 0 ) {
            // check if the next param exists
            if ( i+1 < argc ) {
                Config.setLogConfigFileName( argv[i+1] );
            } else {
                Display.DisplayError( "Improper use of config parameter. Should be followed by config path" );
                return LINUX_ERROR;
            }
        }
    }

    // load APP config and Log config
    result = Config.loadConfig();
    if ( ! result ) {
        return LINUX_ERROR;
    }

    result = LogConfig.loadConfig();
    if ( ! result ) {
        return LINUX_ERROR;
    }

    LogUploader.Cycle();

    return LINUX_NO_ERROR;
}
