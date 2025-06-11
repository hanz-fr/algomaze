#include <iostream>
#include <vector>
#include "../include/render_maze.h"
#include "../include/maze_completed.h"
#include "../include/player_pos.h"

const int row = 26;
const int col = 26;

void renderMaze(int player_row, int player_col, const std::vector<std::vector<bool>> &maze)
{
    for (int row = 0; row < maze.size(); ++row)
    {
        for (int col = 0; col < maze[0].size(); ++col)
        {
            if (row == player_row && col == player_col)
                std::cout << '#'; // player symbol
            else
                std::cout << (maze[row][col] ? char(219) : ' ');
        }
        std::cout << '\n';
    }
}