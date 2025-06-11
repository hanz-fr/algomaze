#include <iostream>
#include <fstream>
#include <vector>
#include "../include/save_maze_to_db.h"

void saveMazeToDB(
    const std::vector<std::vector<bool>>& maze,
    const std::string& filename,
    const std::pair<int, int>& startPos,
    const std::pair<int, int>& endPos
) {
    std::ofstream file(filename, std::ios::app);
    if (!file) {
        std::cerr << "Gagal membuka penyimpanan maze.\n";
        return;
    }

    for (const auto& row : maze) {
        for (bool cell : row) {
            file << (cell ? '1' : '0');
        }
        file << '\n';
    }

    file << "S:" << startPos.first << "," << startPos.second << '\n';
    file << "E:" << endPos.first << "," << endPos.second << '\n';

    file << "---\n"; // delimiter buat batesin antara maze

    file.close();
}
