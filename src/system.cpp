/*
 * system.cpp
 *
 *  Created on: 19 Jan 2019
 *      Author: Gabi
 */

System::System()
{

}

FILE* System::openPipe( STRINGCLASS command )
{
    FILE* pipe;

#ifdef RUNNING_ON_LINUX
    pipe = popen(command.c_str(), "r");
#endif

#ifdef RUNNING_ON_WINDOWS
    pipe = _popen(command, "r");
#endif

    return pipe;
}

void System::closePipe( FILE* pipe )
{
#ifdef RUNNING_ON_LINUX
    pclose(pipe);
#endif

#ifdef RUNNING_ON_WINDOWS
    _pclose(pipe);
#endif
}

STRINGCLASS System::Execute( STRINGCLASS command )
{
    char buffer[128];
    std::string result = "";
    FILE* pipe;

    pipe = this->openPipe( command );

    if ( ! pipe ) {
        return "popen() failed!";
    }

    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        this->closePipe( pipe );
        return "";
    }

    this->closePipe( pipe );

    return result;
}

int System::GetTerminalWidth()
{
    // terminal width
    struct winsize size;
    ioctl( 0, TIOCGWINSZ, (PCHAR) &size );
    return size.ws_col;
}
