#include "console.h"

#include <iostream>
#include <sstream>

void console::clear()
{
#ifndef DEBUG
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
    system("clear");
#endif // _WIN32
#endif // DEBUG
}

void console::show_title()
{
    console::clear();
    std::cout << R"(
 _____             ______ _            _    _            _    
/  __ \ _     _    | ___ \ |          | |  (_)          | |   
| /  \/| |_ _| |_  | |_/ / | __ _  ___| | ___  __ _  ___| | __
| |  |_   _|_   _| | ___ \ |/ _` |/ __| |/ / |/ _` |/ __| |/ /
| \__/\|_|   |_|   | |_/ / | (_| | (__|   <| | (_| | (__|   < 
 \____/            \____/|_|\__,_|\___|_|\_\ |\__,_|\___|_|\_\
                                          _/ |                
                                         |__/                 
    )" << std::endl;
}