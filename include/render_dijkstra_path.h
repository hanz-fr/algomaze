#ifndef RENDER_DIJKSTRA_PATH_H
#define RENDER_DIJKSTRA_PATH_H
#include <vector>

void renderDijkstraPath(int player_row, int player_col, const std::vector<std::vector<bool>> &maze, const std::vector<int>& path = {}, int num_cols = 0);

#endif