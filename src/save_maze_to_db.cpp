#include <iostream>
#include <fstream>
#include <vector>
#include "../include/save_maze_to_db.h"

void saveMazeToDB(const std::vector<std::vector<bool>>& maze, const std::string& filename) {
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

    file << "---\n"; // delimiter buat batesin antara maze

    file.close();
}
