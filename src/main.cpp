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

    std::string argument;

    Setup setup;

    // check command line arguments
    for (i=0; i<argc; i++) {
        // check if we need to run the setup
        argument = argv[i];
        if (argument.compare(SETUP_ARGUMNET1) == 0 || argument.compare(SETUP_ARGUMENT2) == 0) {
            if (i != 1 || argc > 2) {
                return LINUX_ERROR;
            }

            setup.Start();
        }
    }

    return LINUX_NO_ERROR;
}
