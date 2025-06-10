#include <iostream>
#include <fstream>
#include <string>
#include "../include/select_maze.h"

void selectMaze(const std::string &filename, int &selected)
{
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile)
    {
        std::cerr << "Gagal membuka sesi maze.\n";
        return;
    }

    outFile << selected; // tulis ke db currentMaze maze yg dipilih saat ini
}