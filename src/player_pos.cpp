#include "../include/clear_screen.h"
#include "../include/player_pos.h"
#include <iostream>

void showPlayerPos(int col_pos, int row_pos)
{
    clearScreen();
    std::cout << "Position: [" << col_pos << "]"  "[" << row_pos << "]" << std::endl;
}