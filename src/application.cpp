/*
 * application.cpp
 *
 *  Created on: 22 Feb 2019
 *      Author: Gabi
 */

Application::Application()
{
    this->start = clock();
    this->slept = 0;
}

double Application::MeasureRunTime()
{
    double time;

    // app time
    time = (double) ( clock() - this->start ) / CLOCKS_PER_SEC;

    // total time, must convert slept time from miliseconds to seconds
    time = time + ( (double) this->slept / 1000 );

    return time;
}

void Application::Sleep()
{
    // store time slept in miliseconds, not microseconds
    this->slept = this->slept + Config.getUploadDelay() / 1000;

    usleep( Config.getUploadDelay() );
}

void Application::MarkUploadStart()
{
    this->uploadStart = clock();
}

double Application::MeasureUploadTime()
{
    double time;

    // upload time, will be in miliseconds
    time = (double) ( clock() - this->uploadStart ) / CLOCKS_PER_SEC;

    return time;
}
