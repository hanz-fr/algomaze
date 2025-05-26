#include <iostream>
#include <vector>
#include "../include/render_maze.h"

const int row = 25;
const int col = 25;

void renderMaze(int player_row, int player_col, const std::vector<std::vector<bool>> &maze) {
    for (int col = 0; col < maze.size(); ++col) {
        for (int row = 0; row < maze[0].size(); ++row) {
            if (row == player_row && col == player_col)
                std::cout << '#'; // player symbol
            else
                std::cout << (maze[col][row] ? char(219) : ' ');
        }
        std::cout << '\n';
    }
}