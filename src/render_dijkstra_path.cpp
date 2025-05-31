#include <iostream>
#include <vector>
#include <set> 
#include "../include/render_dijkstra_path.h"

void renderDijkstraPath(int player_row, int player_col, const std::vector<std::vector<bool>> &maze, const std::vector<int>& path, int num_cols)
{
    if (maze.empty()) { 
        return;
    }

    // Menyimpan koordinat jalur untuk pengecekan cepat
    std::set<std::pair<int, int>> path_coords;
    if (!path.empty() && num_cols > 0) { // Hanya proses path jika ada dan num_cols valid
        for (int node_id : path) {
            int r = node_id / num_cols;
            int c = node_id % num_cols;
            
            // Memastikan koordinat hasil konversi berada dalam batas maze
            if (r >= 0 && r < maze.size() && c >= 0 && c < maze[0].size()) {
                path_coords.insert({r, c});
            }
        }
    }

    // Loop untuk menggambar maze baris per baris
    for (size_t r_idx = 0; r_idx < maze.size(); ++r_idx)
    {
        // Loop untuk menggambar setiap sel dalam satu baris
        for (size_t c_idx = 0; c_idx < maze[0].size(); ++c_idx)
        {
            if (static_cast<int>(r_idx) == player_row && static_cast<int>(c_idx) == player_col) {
                std::cout << '#'; // Simbol pemain
            } else if (path_coords.count({static_cast<int>(r_idx), static_cast<int>(c_idx)})) { // Cek apakah sel ini bagian dari jalur
                std::cout << '*'; // Simbol untuk jalur
            } else {
                // Mencetak tembok (true) atau jalan kosong (false)
                std::cout << (maze[r_idx][c_idx] ? char(219) : ' '); 
            }
        }
        std::cout << '\n'; // Pindah ke baris baru setelah satu baris selesai dicetak
    }
}