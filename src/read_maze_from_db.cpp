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
                return currentMaze;
            }
            currentMaze.clear();
            ++currentIndex;
        }
        else if (line.rfind("S:", 0) == 0 || line.rfind("E:", 0) == 0)
        {
            // abaikan baris start/end position
            continue;
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

    if (currentIndex == index)
    {
        return currentMaze;
    }

    std::cerr << "Indeks maze di luar jangkauan.\n";
    return {};
}

std::pair<std::pair<int, int>, std::pair<int, int>> getCurrentMazeStartAndFinish(const std::string& filename, size_t index)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Gagal membuka penyimpanan maze.\n";
        return {{-1, -1}, {-1, -1}};
    }

    std::string line;
    size_t currentIndex = 0;
    std::pair<int, int> start = {-1, -1};
    std::pair<int, int> end = {-1, -1};

    bool insideTargetMaze = false;

    while (std::getline(file, line))
    {
        if (line == "---")
        {
            if (insideTargetMaze)
            {
                break; // finished reading target maze
            }

            currentIndex++;
            continue;
        }

        if (currentIndex == index)
        {
            insideTargetMaze = true;

            if (line.rfind("S:", 0) == 0)
            {
                size_t comma = line.find(',');
                if (comma != std::string::npos)
                {
                    int x = std::stoi(line.substr(2, comma - 2));
                    int y = std::stoi(line.substr(comma + 1));
                    start = {x, y};
                }
            }
            else if (line.rfind("E:", 0) == 0)
            {
                size_t comma = line.find(',');
                if (comma != std::string::npos)
                {
                    int x = std::stoi(line.substr(2, comma - 2));
                    int y = std::stoi(line.substr(comma + 1));
                    end = {x, y};
                }
            }
        }
    }

    return {start, end};
}