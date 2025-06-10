#ifndef SAVE_MAZE_TO_DB_H
#define SAVE_MAZE_TO_DB_H
#include <vector>
#include <string>

void saveMazeToDB(const std::vector<std::vector<bool>>& maze, const std::string& filename);

#endif