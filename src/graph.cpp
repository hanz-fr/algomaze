#include "../include/graph.h"
#include <iostream> 

std::map<int, std::vector<int>> buildGraph(const std::vector<std::vector<bool>>& maze_data) {
    std::map<int, std::vector<int>> adjList;
    if (maze_data.empty()) {
        return adjList; // Kembalikan list kosong jika maze kosong
    }

    int num_rows = maze_data.size();
    int num_cols = maze_data[0].size();

    for (int r = 0; r < num_rows; ++r) {
        for (int c = 0; c < num_cols; ++c) {
            // Jika sel saat ini adalah jalur (false (0))
            if (!maze_data[r][c]) {
                int current_node_id = r * num_cols + c;
                adjList[current_node_id] = {}; // Inisialisasi daftar tetangga untuk node ini

                // Cek tetangga (atas, bawah, kiri, kanan)
                int dr[] = {-1, 1, 0, 0}; // Perubahan baris 
                int dc[] = {0, 0, -1, 1}; // Perubahan kolom 

                for (int i = 0; i < 4; ++i) {
                    int neighbor_r = r + dr[i];
                    int neighbor_c = c + dc[i];

                    // Cek apakah tetangga valid (dalam batas maze dan juga jalur)
                    if (neighbor_r >= 0 && neighbor_r < num_rows &&
                        neighbor_c >= 0 && neighbor_c < num_cols &&
                        !maze_data[neighbor_r][neighbor_c]) {
                        
                        int neighbor_node_id = neighbor_r * num_cols + neighbor_c;
                        adjList[current_node_id].push_back(neighbor_node_id);
                    }
                }
            }
        }
    }
    return adjList;
}