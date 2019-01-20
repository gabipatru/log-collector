/*
 * setup.cpp
 *
 *  Created on: 19 Jan 2019
 *      Author: Gabi
 */

Setup::Setup()
{
    class System sys;
    class Display disp;

    // init the system class
    this->System = sys;
    this->Display = disp;
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
    this->Display.DisplayTitle("Starting Setup !");

    printf("Press any key to continue! \n\n");
    getchar();

    return 1;
}

int Setup::Step1()
{
    int correctHost;
    PCHAR buffer;
    STRINGCLASS hostname, Title("Get hostname (1 of ");

    Title = Title + SETUP_NUMBER_OF_STEPS;
    Title = Title + ")";

    this->Display.DisplayTitle(Title.c_str());

    // get the hostname
    hostname = this->System.Execute("hostname");

    // info display
    printf("Found the hostname %s%s%s\n\n", LINUX_TERMINAL_YELLOW, hostname.c_str(), LINUX_TERMINAL_NOCOLOR);

    // ask if information is correct
    correctHost = this->Display.DisplayYesNoQuestion("Is this correct ?");

    // if the hostname is incorrect, the user must input the correct hostname
    if (!correctHost) {
        printf("Enter new Hostname: ");
        std::cin >> hostname;
    }

    // save the hostname in the Config class
    conf.setHostname(hostname);

    return 1;
}
