#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "../include/delete_oldest_maze_from_db.h"

void deleteOldestMazeFromDB(const std::string &filename)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cerr << "Gagal membuka penyimpanan maze.\n";
        return;
    }

    std::vector<std::string> mazeBlocks; // simpen 1 blok maze (keseluruhan maze) dalam bentuk vector
    std::string line, currentBlock;

    while (std::getline(inFile, line))
    {
        if (line == "---") // kalau barisnya ---, berarti itu udah beres
        {
            mazeBlocks.push_back(currentBlock);
            currentBlock.clear();
        }
        else // kalau nggak, terus tambah
        {
            /*
                Nanti setiap line baru, currentBlock bentuknya kek gini:
                "101\n010\n101\n"
            */
            currentBlock += line + "\n";
        }
    }

    if (!currentBlock.empty())
    {
        mazeBlocks.push_back(currentBlock);
    }

    inFile.close();

    if (mazeBlocks.empty())
    {
        std::cerr << "Tidak ada maze yang dapat di delete.\n";
        return;
    }

    // hapus maze tsb
    mazeBlocks.erase(mazeBlocks.begin());

    // tulis ulang file
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile)
    {
        std::cerr << "Gagal membuka penyimpanan storage.\n";
        return;
    }

    for (size_t i = 0; i < mazeBlocks.size(); ++i)
    {
        outFile << mazeBlocks[i];
        outFile << "---\n";
    }

    outFile.close();
    std::cout << "Maze terlama dari antrian penyimpanan berhasil dihapus.\n";
}