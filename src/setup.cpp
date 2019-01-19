/*
 * setup.cpp
 *
 *  Created on: 19 Jan 2019
 *      Author: Gabi
 */

/**
 * The default constructor
 */
Setup::Setup()
{
    // terminal width
    struct winsize size;
    ioctl( 0, TIOCGWINSZ, (char *) &size );
    this->terminalWidth = size.ws_col;
}

/**
 * Display a tile message
 */
void Setup::DisplayTitle(const char msg[])
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

    printf("Press any key to continue! \n\n");

    getchar();
}

/**
 * Start the setup.
 * Should only be called when the command line argument is detected.
 */
void Setup::Start()
{
    // check if the setup was previously started
    if (this->setupStarted == 1) {
        printf("Error! Setup already started!\n");
        return;
    }
    this->setupStarted = 1;

    this->DisplayTitle("Starting Setup !");
}
