#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H
#include <vector>

bool isPlayerMoveValid(int new_row, int new_col, const std::vector<std::vector<bool>> &maze);

#endif