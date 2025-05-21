#include <iostream>
#include "../include/clear_screen.h"

void clearScreen()
{
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux / Mac
    #endif
}
