/*
 * system.h
 *
 *  Created on: 19 Jan 2019
 *      Author: Gabi
 */

#ifndef SRC_SYSTEM_H_
#define SRC_SYSTEM_H_

class System
{
public:
    /**
     * Default constructor
     */
    System();

    /**
     * Execute a system command and return the output
     */
    CPCHAR Execute(const char[]);

    /**
     * Get the terminal width
     */
    int GetTerminalWidth();
};

#include <stdexcept>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "system.cpp"

#endif /* SRC_SYSTEM_H_ */
