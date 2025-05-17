#include <conio.h>
#include <iostream>
#include "../include/keyinp.h"

void printRowCol()
{
    std::cout << "[" << row_pos << "]" << "[" << col_pos << "]" << std::endl;
}

void moveUp(int current_row)
{
    int res = (current_row > 0) ? row_pos -= 1 : -1;
}

void moveDown(int current_row)
{
    int res = (current_row >= 0) ? row_pos += 1 : -1;
}

void moveLeft(int current_col)
{
    int res = (current_col > 0) ? col_pos -= 1 : -1;
}

void moveRight(int current_col)
{
    int res = (current_col >= 0) ? col_pos += 1 : -1;
}

int main()
{
    int c = 0;

    while (1)
    {
        c = getch();

        if (c == 0 || c == 224)
        {
            c = getch();
            switch (c)
            {
            case KEY_UP:
                moveUp(row_pos);
                printRowCol();
                break;
            case KEY_DOWN:
                moveDown(row_pos);
                printRowCol();
                break;
            case KEY_LEFT:
                moveLeft(col_pos);
                printRowCol();
                break;
            case KEY_RIGHT:
                moveRight(col_pos);
                printRowCol();
                break;
            default:
                std::cout << "Unknown special key: " << c << std::endl;
                break;
            }
        }
        else
        {
            std::cout << "Not an arrow key." << std::endl;
        }
    }

    return 0;
}
