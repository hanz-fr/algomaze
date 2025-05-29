#include "../include/render_maze.h"
#include "../include/clear_screen.h"
#include "../include/keyinp.h"
#include "../include/player_movement.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>

bool isPlayerMoveValid(int new_row, int new_col, const std::vector<std::vector<bool>> &maze)
{
    if (new_row >= 0 && new_row < maze.size() && new_col >= 0 && new_col < maze[0].size())
    {
        return maze[new_row][new_col] == 0; // check if wall or not, return true (valid) if not a wall
    }
    return true; // outside boundary will be checked by isCompleted()
    
};