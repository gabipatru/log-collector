/*
 * help.cpp
 *
 *  Created on: 20 Jan 2019
 *      Author: Gabi
 */

Help::Help()
{

}

void Help::DisplayHelp()
{
    printf( "\n");

    printf( "Client for Log Collector\n" );
    printf( "Usage: log-client.exe <argument list>\n\n" );

    printf( "  Arguments: \n" );
    printf( "      -H    --help                        Display this help\n" );
    printf( "      -S    --setup                       Run the setup\n" );
    printf( "      -L    --log                         Process only the log specified by this path" );

    printf( "\n\n\n" );
}
