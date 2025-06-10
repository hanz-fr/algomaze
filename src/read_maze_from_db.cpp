#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "../include/read_maze_from_db.h"

std::vector<std::vector<bool>> readMazeFromDB(const std::string &filename, size_t index)
{
    std::ifstream file(filename);
    std::vector<std::vector<bool>> currentMaze;
    std::string line;
    size_t currentIndex = 0;

    if (!file)
    {
        std::cerr << "Gagal membuka penyimpanan maze.\n";
        return {};
    }

    while (std::getline(file, line))
    {
        if (line == "---")
        {
            if (currentIndex == index)
            {
                return currentMaze; // output maze indeks yg dicari
            }
            currentMaze.clear(); // kalau gaada, reset, terus lanjut cari
            ++currentIndex;
        }
        else
        {
            if (currentIndex == index)
            {
                std::vector<bool> row;
                for (char ch : line)
                {
                    row.push_back(ch == '1');
                }
                currentMaze.push_back(row);
            }
        }
    }

    // pengkondisian untuk maze terakhir karena gaada ---- (delimiter)
    if (currentIndex == index)
    {
        return currentMaze;
    }

    std::cerr << "Indeks maze diluar jangkauan.\n";
    return {};
}