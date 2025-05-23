#include "../include/clear_screen.h"
#include "../include/player_pos.h"
#include <iostream>

void showPlayerPos(int row_pos, int col_pos)
{
    clearScreen();
    std::cout << "[" << row_pos << "]" << "[" << col_pos << "]" << std::endl;
}