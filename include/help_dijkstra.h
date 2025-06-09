#include <vector>
#include <map>

void showHelpDijkstra(
    int player_row_pos, int player_col_pos,
    int maze_exit_row, int maze_exit_col,
    const std::vector<std::vector<bool>>& maze,
    const std::map<int, std::vector<int>>& maze_graph);
