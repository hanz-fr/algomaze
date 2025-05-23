#include "../include/clear_screen.h"
#include "../include/player_pos.h"
#include <iostream>


int player_row_pos ;
int player_col_pos ;

// Fungsi untuk mencetak posisi pemain
void printRowCol(int row_pos, int col_pos)
{
    std::cout << "[" << row_pos << "]" << "[" << col_pos << "]" << std::endl;
}