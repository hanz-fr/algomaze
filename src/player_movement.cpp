#include "../include/render_maze.h"
#include "../include/clear_screen.h"
#include "../include/keyinp.h"
#include "../include/player_movement.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>

bool isPlayerMoveValid(int new_row, int new_col, const std::vector<std::vector<bool>> &maze)
{
    if (new_col < 0 || new_col >= maze.size()) // X axis
        return false;
    if (new_row < 0 || new_row >= maze[0].size()) // Y axis
        return false;                   
    return maze[new_col][new_row] == 0; 
};