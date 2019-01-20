/*
 * system.cpp
 *
 *  Created on: 19 Jan 2019
 *      Author: Gabi
 */

System::System()
{

}

CPCHAR System::Execute(const char command[])
{
    char buffer[128];
    std::string result = "";
    FILE* pipe;

    if (RUNNING_ON_LINUX) {
        pipe = popen(command, "r");
    } else {
        //FILE* pipe = _popen(command, "r");
    }

    if (!pipe) {
        return "popen() failed!";
    }
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        if (RUNNING_ON_LINUX) {
            pclose(pipe);
        } else {
            //_pclose();
        }
        return "";
    }

    if (RUNNING_ON_LINUX) {
        pclose(pipe);
    } else {
        //_pclose();
    }
    return result.c_str();
}

int System::GetTerminalWidth()
{
    // terminal width
    struct winsize size;
    ioctl( 0, TIOCGWINSZ, (PCHAR) &size );
    return size.ws_col;
}
