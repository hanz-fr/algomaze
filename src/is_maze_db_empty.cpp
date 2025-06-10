#include <iostream>
#include <fstream>
#include <string>

int mazeCount(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Gagal membuka penyimpanan maze.\n";
        return false;
    }

    int mazeTotal = 0;
    bool inMaze = false;
    std::string line;

    while (std::getline(file, line)) {
        if (line == "---") {
            mazeTotal++;
        }
    }

    return mazeTotal;
}