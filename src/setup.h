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

class Setup
{

private:
    int setupStarted;
    int terminalWidth;
    void DisplayTitle(const char[]);
    int GetTerminalWidth();

    void Step1();

public:
    Setup();
    void Start();
};

#endif /* SRC_SETUP_H_ */

#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <iostream>

#include "setup.cpp"
