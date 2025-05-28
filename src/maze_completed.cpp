#include <stdio.h>
#include <iostream>
#include "../include/maze_completed.h"
#include "../include/maze.h"

bool isCompleted(int player_row_pos, int player_col_pos, std::vector<std::vector<bool>> maze)
{
    int maze_row = maze.size();
    int maze_col = maze[0].size();

    bool result = ((player_row_pos < 0) || (player_row_pos >= maze_row) || (player_col_pos < 0) || (player_col_pos >= maze_col));

    return result;
}