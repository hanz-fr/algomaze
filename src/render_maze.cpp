#include "../include/render_maze.h" // Pastikan path ini benar
#include <iostream>


// Hapus const int row dan col dari sini jika ada, karena ukuran diambil dari vector

void renderMaze(const std::vector<std::vector<bool>>& maze_data, int current_player_row, int current_player_col) {
    if (maze_data.empty()) {
        std::cerr << "Peringatan: Mencoba merender maze kosong." << std::endl;
        return;
    }

    // Iterasi melalui maze_data untuk menggambar
    for (int r = 0; r < maze_data.size(); ++r) {
        for (int c = 0; c < maze_data[r].size(); ++c) {
            if (r == current_player_row && c == current_player_col) {
                std::cout << 'P'; // Karakter untuk pemain
            } else {
                // Asumsi: true (1) adalah tembok, false (0) adalah jalur
                std::cout << (maze_data[r][c] ? char(219) : ' '); 
            }
        }
        std::cout << std::endl;
    }
}