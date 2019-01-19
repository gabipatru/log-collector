/*
 * setup.cpp
 *
 *  Created on: 19 Jan 2019
 *      Author: Gabi
 */

Setup::Setup()
{
    class System sys;

    // init the system class
    this->System = sys;
    this->terminalWidth = this->System.GetTerminalWidth();
}

void Setup::DisplayTitle(CPCHAR msg)
{
    int i, extraStars;

    std::string StarLine(this->terminalWidth, '*');

    // clear the console
    system(CLEAR_SCREEN);

    printf("%s%s\n", LINUX_TERMINAL_LIGHTGREEN, StarLine.c_str());
    printf("%s\n", "*");
    printf("* %s%s%s\n", LINUX_TERMINAL_YELLOW, msg, LINUX_TERMINAL_LIGHTGREEN);
    printf("%s\n", "*");
    printf("%s%s\n\n", StarLine.c_str(), LINUX_TERMINAL_NOCOLOR);
}

void Setup::Start()
{
    // check if the setup was previously started
    if (this->setupStarted == 1) {
        printf("Error! Setup already started!\n");
        return;
    }
    this->setupStarted = 1;

    if (this->Step0() != 1) {
        return;
    }
    if (this->Step1() != 1) {
        return;
    }
}

int Setup::Step0()
{
    this->DisplayTitle("Starting Setup !");

    printf("Press any key to continue! \n\n");
    getchar();

    return 1;
}

int Setup::Step1()
{
    CPCHAR hostname;
    PCHAR title;
    std::string Title("Get hostname (1 of ");

    Title = Title + SETUP_NUMBER_OF_STEPS;
    Title = Title + ")";


    this->DisplayTitle(Title.c_str());

    // get the hostname
    hostname = this->System.Execute("hostname");

    // info display
    printf("Found the hostname %s%s%s\n\n", LINUX_TERMINAL_YELLOW, hostname, LINUX_TERMINAL_NOCOLOR);

    return 1;
}
