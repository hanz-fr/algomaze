#ifndef KEYINP_H
#define KEYINP_H
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int row_pos = 0;
int col_pos = 0;

void printRowCol();

void moveUp(int current_row);

void moveDown(int current_row);

void moveLeft(int current_col);

void moveRight(int current_col);

#endif