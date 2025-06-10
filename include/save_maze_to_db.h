#ifndef SAVE_MAZE_TO_DB_H
#define SAVE_MAZE_TO_DB_H
#include <vector>
#include <string>

void saveMazeToDB(const std::vector<std::vector<bool>> &maze, const std::string &filename, const std::pair<int, int> &startPos, const std::pair<int, int> &endPos);

#endif