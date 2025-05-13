#include "../include/maze.h"
#include <stdio.h>
#include <iostream>
#include <vector>


int main()
{
    std::vector<std::vector<bool>> maze = createMaze();

    for (const auto& row : maze) {
        for (bool cell : row) {
            std::cout << (cell ? char(219) : ' ');
        }
        std::cout << std::endl;
    }

    return 0;
}