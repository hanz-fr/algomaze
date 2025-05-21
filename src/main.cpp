#include "../include/maze.h"
#include "../include/empty_maze.h"
#include "../include/keyinp.h"
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <vector>

int main()
{
    /* std::vector<std::vector<bool>> maze = createEmptyMaze();

    for (const auto& row : maze) {
        for (bool cell : row) {
            std::cout << (cell ? char(219) : ' ');
        }
        std::cout << std::endl;
    } */

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
                break;
            case KEY_DOWN:
                break;
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
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