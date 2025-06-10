#ifndef SAVE_MAZE_MODAL_H
#define SAVE_MAZE_MODAL_H
#include <vector>
#include <string>

void saveMazeModal(std::vector<std::vector<bool>> maze, std::string& message_result, const std::pair<int, int> &startPos, const std::pair<int, int> &endPos);

#endif