/*
 * help.h
 *
 *  Created on: 20 Jan 2019
 *      Author: Gabi
 */

#ifndef SRC_HELP_H_
#define SRC_HELP_H_

/**
 * Help Constants
 */
#define HELP_ARGUMENT1 "--help"
#define HELP_ARGUMENT2 "-H"

class Help
{
public:
    /**
     * Default constructor
     */
    Help();

    /**
     * Display the help
     */
    void DisplayHelp();
};

#include "help.cpp"

#endif /* SRC_HELP_H_ */
