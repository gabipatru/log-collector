/*
 * setup.h
 *
 *  Created on: 19 Jan 2019
 *      Author: Gabi
 */

#ifndef SRC_SETUP_H_
#define SRC_SETUP_H_

/**
 * Setup Constants
 */
#define SETUP_ARGUMNET1 "--setup"
#define SETUP_ARGUMENT2 "-S"

#define SETUP_NUMBER_OF_STEPS "1";

class Setup
{

private:
    int setupStarted;

    class System System;
    class Display Display;

    /**
     * Step 0 - display setup start message
     */
    int Step0();

    /**
     * Step 1 - get hostname
     */
    int Step1();

public:
    /**
     * The default constructor
     * Get the terminal width
     */
    Setup();

    /**
     * Start the setup.
     * Should only be called when the command line argument is detected.
     */
    void Start();
};

#include <iostream>

#include "setup.cpp"

#endif /* SRC_SETUP_H_ */
