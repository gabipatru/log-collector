/*
 * display.h
 *
 *  Created on: 20 Jan 2019
 *      Author: Gabi
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

class Display
{
public:
    int terminalWidth;

    class System System;

    /**
     * Default constructor
     */
    Display();

    /**
    * Display a tile message
    */
    void DisplayTitle(CPCHAR);

    /**
     * Display a YES/NO question and return if the user pressed Yes (1) or No (0)
     */
    int DisplayYesNoQuestion(CPCHAR question);
};

#include <stdlib.h>

#include "display.cpp"

#endif /* SRC_DISPLAY_H_ */
