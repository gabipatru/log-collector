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

int main (int argc, PCHAR argv[])
{
    // vars
    int i;
    LogItem Item("NULL", "NULL", "NULL");

    STRINGCLASS argument;

    Setup Setup;
    Help Help;
    LogConfig LogConfig;

    // check command line arguments
    for (i=0; i<argc; i++) {
        argument = argv[i];

        // check if we need to run the setup
        if (argument.compare(SETUP_ARGUMNET1) == 0 || argument.compare(SETUP_ARGUMENT2) == 0) {
            if (i != 1 || argc > 2) {
                return LINUX_ERROR;
            }

            Setup.Start();

            return LINUX_NO_ERROR;
        }

        // check if we have to display the help
        if (argument.compare(HELP_ARGUMENT1) == 0 || argument.compare(HELP_ARGUMENT2) == 0) {
            Help.DisplayHelp();

            return LINUX_NO_ERROR;
        }
    }

    LogConfig.loadConfig();

    return LINUX_NO_ERROR;
}
