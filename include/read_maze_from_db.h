#ifndef READ_MAZE_FROM_DB_H
#define READ_MAZE_FROM_DB_H
#include <vector>
#include <string>

std::vector<std::vector<bool>> readMazeFromDB(const std::string& filename, size_t index);

#endif