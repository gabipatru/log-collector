/*
 * display.cpp
 *
 *  Created on: 20 Jan 2019
 *      Author: Gabi
 */

Display::Display()
{
    class System sys;

    // init the system class
    this->System = sys;
    this->terminalWidth = this->System.GetTerminalWidth();
}

void Display::DisplayTitle(CPCHAR msg)
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

int Display::DisplayYesNoQuestion(CPCHAR question)
{
    char c;

    printf("%s\n", question);
    printf("[ %sY%s ] or [ %sN%s ]", LINUX_TERMINAL_WHITE, LINUX_TERMINAL_NOCOLOR, LINUX_TERMINAL_WHITE, LINUX_TERMINAL_NOCOLOR);
    c = getchar();
    while (c != 'Y' && c != 'N' && c != 'y' && c != 'n') {
        c = getchar();
    }

    if (c == 'Y' || c == 'y') {
        return 1;
    } else {
        return 0;
    }
}
