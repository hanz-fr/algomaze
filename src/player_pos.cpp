#include "../include/clear_screen.h"
#include <iostream>

void printRowCol(int row_pos, int col_pos)
{
    clearScreen();
    std::cout << "[" << row_pos << "]" << "[" << col_pos << "]" << std::endl;
}