#include <iostream>
#include "../include/read_maze_from_db.h"

int main()
{
    std::vector<std::vector<bool>> maze;

    auto [start, end] = getCurrentMazeStartAndFinish("database/maze.txt", 1);
    std::cout << "Start: (" << start.first << "," << start.second << ")\n";
    std::cout << "End: (" << end.first << "," << end.second << ")\n";

    maze = readMazeFromDB("database/maze.txt", 2);

    std::cout << maze[0].size() << "\n";
}