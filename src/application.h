/*
 * application.h
 *
 *  Created on: 22 Feb 2019
 *      Author: Gabi
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <time.h>

class Application
{
public:
    /**
     * Default constructor
     */
    Application();

    /**
     * Get the run time of the app in seconds
     */
    double MeasureRunTime();

    /**
     * Functions for marking upload start and mesauring upload time in miliseconds
     */
    void MarkUploadStart();
    double MeasureUploadTime();

    /**
     * Idle for a number of miliseconds
     */
    void Sleep();

private:
    clock_t start;
    clock_t uploadStart;
    unsigned long int slept;
};

#include "application.cpp"

class Application Application;

#endif /* APPLICATION_H_ */
