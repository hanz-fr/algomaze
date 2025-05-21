#include "../include/keyinp.h"
#include <conio.h>
#include <iostream>

int moveUp(int current_row)
{
    int res = (current_row > 0) ? current_row -= 1 : current_row;
    return res;
}

int moveDown(int current_row)
{
    int res = (current_row >= 0) ? current_row += 1 : current_row;
    return res;
}

int moveLeft(int current_col)
{
    int res = (current_col > 0) ? current_col -= 1 : current_col;
    return res;
}

int moveRight(int current_col)
{
    int res = (current_col >= 0) ? current_col += 1 : current_col;
    return res;
}
