#ifndef RENDER_MAZE_H
#define RENDER_MAZE_H
#include <vector>

void renderMaze(int player_row, int player_col, const std::vector<std::vector<bool>> &maze, const std::vector<int>& path = {}, int num_cols = 0);
#endif