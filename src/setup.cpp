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
        Title = "Get client";
        break;
    case 2:
        Title = "Get hostname";
        break;
    case 3:
        Title = "Get ip address";
        break;
    case 4:
        Title = "Get Application Path";
        break;
    case 5:
        Title = "Set up API POST URL";
        break;
    default:
        Title = "Unknown Step";
        break;
    }

    snprintf(buffer, sizeof(buffer), " (step %d of %d)", step, SETUP_NUMBER_OF_STEPS);
    Title = Title + buffer;
    return Title;
}

int Setup::Start()
{
    int result;

    // check if the setup was previously started
    if (this->setupStarted == 1) {
        this->Display.DisplayError("Error! Setup already started!\n");
        return 0;
    }
    this->setupStarted = 1;

    if (this->Step0() != 1) {
        return 0;
    }
    if (this->Step1() != 1) {
        return 0;
    }
    if (this->Step2() != 1) {
        return 0;
    }
    if (this->Step3() != 1) {
        return 0;
    }
    if (this->Step4() != 1) {
        return 0;
    }
    if (this->Step5() != 1) {
        return 0;
    }

    result = Config.saveConfig();
    if (! result) {
        this->Display.DisplayError("Error !!! Config file could not be saved !");
        return 0;
    }

    system( CLEAR_SCREEN );
    this->Display.DisplayMessage("Config file saved.");

    return 1;
}

int Setup::Step0()
{
    int continueSetup;
    FILE *file;

    this->Display.DisplayTitle("Starting Setup !");

    // check if a config file exists
    if (file = fopen(CONFIG_FILE_NAME, "r")) {
        fclose(file);
        printf("WARNING!! A config file exists. If you continue setup, the file will be overwritten \n\n");
        continueSetup = this->Display.DisplayYesNoQuestion("Continue setup ?");
        if (! continueSetup) {
            return 0;
        }
    } else {
        printf("Press any key to continue! \n\n");
        getchar();
    }

    return 1;
}

int Setup::Step1()
{
    STRINGCLASS client, Title;

    Title = this->getTitleForStep( this->getNextStep() );
    this->Display.DisplayTitle( Title.c_str() );

    printf( "Enter client name: " );
    std::cin >> client;

    Config.setClient( client );

    return 1;
}

int Setup::Step2()
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
    if (! correctHost) {
        printf("Enter new Hostname: ");
        std::cin >> hostname;
    }

    // save the hostname in the Config class
    Config.setHostname(hostname);

    return 1;
}

int Setup::Step3()
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

    // if the ip address is incorrect, the user must input the correct ip address
    if (! correctIpAddress) {
        printf("Enter new IP Address: ");
        std::cin >> ipAddress;
    }

    // save the IP Address to the Config class
    Config.setIpAddress(ipAddress);

    return 1;
}

int Setup::Step4()
{
    int correctPath;
    STRINGCLASS path, Title;

    Title = this->getTitleForStep(this->getNextStep());
    this->Display.DisplayTitle(Title.c_str());

    // get application path
    path = SETUP_DEFAULT_PATH;

    // info display
    printf("Found the path %s%s%s\n\n", LINUX_TERMINAL_YELLOW, path.c_str(), LINUX_TERMINAL_NOCOLOR);

    // ask if information is correct
    correctPath = this->Display.DisplayYesNoQuestion("Is this correct ?");

    // if the path is incorrect, the user must input the correct path
    if (! correctPath) {
        printf("Enter new Path: ");
        std::cin >> path;
    }

    Config.setPath(path);

    return 1;
}

int Setup::Step5()
{
    int correctApi;
    STRINGCLASS url, Title;

    Title = this->getTitleForStep(this->getNextStep());
    this->Display.DisplayTitle(Title.c_str());

    // get API POST URL
    url = SETUP_DEFAULT_API_URL;

    // info display
    printf("Found the API URL %s%s%s\n\n", LINUX_TERMINAL_YELLOW, url.c_str(), LINUX_TERMINAL_NOCOLOR);

    // ask if the information is correct
    correctApi = this->Display.DisplayYesNoQuestion("Is this correct ?");

    // if the API URL is incorrect, the user must input the correct API URL
    if (! correctApi) {
        printf("Enter new API URL: ");
        std::cin >> url;
    }

    Config.setApiUrl( url );

    return 1;
}
