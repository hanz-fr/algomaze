#include <stdio.h>
#include "../include/maze_completed.h"

bool isCompleted(int player_row_pos, int player_col_pos, int exit_row, int exit_col)
{
    return ((player_row_pos == exit_row) && (player_col_pos == exit_col));
}