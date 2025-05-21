#ifndef KEYINP_H
#define KEYINP_H

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void printRowCol();

int moveUp(int current_row);

int moveDown(int current_row);

int moveLeft(int current_col);

int moveRight(int current_col);

#endif