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
    this->setupStarted = 0;
    this->step = 0;
}

int Setup::getNextStep()
{
    this->step++;
    return this->step;
}

STRINGCLASS Setup::getTitleForStep(int step)
{
    STRINGCLASS Title;
    char buffer[150];

    // titles for each step
    switch (step) {
    case 1:
        Title = "Get hostname";
        break;
    case 2:
        Title = "Get ip address";
        break;
    default:
        Title = "Unknown Step";
        break;
    }

    snprintf(buffer, sizeof(buffer), " (step %d of %s)", step, SETUP_NUMBER_OF_STEPS);
    Title = Title + buffer;
    return Title;
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
    if (this->Step2() != 1) {
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
    STRINGCLASS hostname, Title;

    Title = this->getTitleForStep(this->getNextStep());
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
    Config.setHostname(hostname);

    return 1;
}

int Setup::Step2()
{
    int correctIpAddress;
    STRINGCLASS ipAddress, Title;

    Title = this->getTitleForStep(this->getNextStep());
    this->Display.DisplayTitle(Title.c_str());

    // get the ip address
    ipAddress = this->System.Execute("hostname -I");

    // info display
    printf("Found the ip address %s%s%s\n\n", LINUX_TERMINAL_YELLOW, ipAddress.c_str(), LINUX_TERMINAL_NOCOLOR);

    // ask if information is correct
    correctIpAddress = this->Display.DisplayYesNoQuestion("Is this correct ?");

    // if the hostname is incorrect, the user must input the correct hostname
    if (!correctIpAddress) {
        printf("Enter new IP Address: ");
        std::cin >> ipAddress;
    }

    // save the IP Address to the Config class
    Config.setIpAddress(ipAddress);

    return 1;
}
