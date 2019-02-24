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

#define SETUP_DEFAULT_PATH "/home/gabi/log-client"
#define SETUP_DEFAULT_API_URL "http://127.0.0.1:8080/upload"

#define SETUP_NUMBER_OF_STEPS 5

class Setup
{

private:
    int setupStarted;
    int step;

    class System System;
    class Display Display;

    /**
     * Increment the current step and return the result
     */
    int getNextStep();

    /**
     * Return a string representing the title for the step
     */
    STRINGCLASS getTitleForStep( int );

    /**
     * Step 0 - display setup start message and check if the config file exists
     */
    int Step0();

    /**
     * Step1 - get the client
     */
    int Step1();

    /**
     * Step 2 - get hostname
     */
    int Step2();

    /**
     * Step 3 - get ip address
     */
    int Step3();

    /**
     * Step 4 - get the application path
     */
    int Step4();

    /**
     * Step 5 - set up the API POST URL
     */
    int Step5();

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
    int Start();
};

#include "setup.cpp"

#endif /* SRC_SETUP_H_ */
