#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <vector> 
#include <map>    

#include "../include/player_movement.h"
#include "../include/keyinp.h"
#include "../include/clear_screen.h"
#include "../include/render_maze.h"
#include "../include/maze.h"
#include "../include/player_pos.h"
#include "../include/vector_to_graph.h"
#include "../include/maze_completed.h"
#include "../include/dijkstra.h" 

int main()
{
    // Inisialisasi maze
    std::vector<std::vector<bool>> maze = initiateMaze();
    if (maze.empty() || maze[0].empty()) {
        std::cerr << "Error: Maze tidak berhasil diinisialisasi atau kosong." << std::endl;
        return 1;
    }
    std::map<int, std::vector<int>> maze_graph = buildGraph(maze); // Konversi maze ke graph

    int num_rows = maze.size();
    int num_cols = maze[0].size();

    // Posisi awal pemain (pastikan ini adalah jalur yang valid: maze[row][col] == 0)
    int player_row_pos = 0;
    int player_col_pos = 1;

    // Posisi keluar labirin (pastikan ini adalah jalur yang valid: maze[row][col] == 0)
    int maze_exit_row = 25;
    int maze_exit_col = 16;

    // Konversi posisi awal dan akhir ke ID node
    int start_node_id = player_row_pos * num_cols + player_col_pos;
    int end_node_id = maze_exit_row * num_cols + maze_exit_col;

    // Validasi apakah node awal dan akhir ada di graph (merupakan jalur)
    if (maze_graph.find(start_node_id) == maze_graph.end()) {
        std::cerr << "Error: Posisi awal pemain (" << player_row_pos << "," << player_col_pos
                  << ") berada di tembok atau di luar batas." << std::endl;
        return 1;
    }
    if (maze_graph.find(end_node_id) == maze_graph.end()) {
        std::cerr << "Error: Posisi keluar maze (" << maze_exit_row << "," << maze_exit_col
                  << ") berada di tembok atau di luar batas." << std::endl;
        return 1;
    }

    // Cari jalur terpendek menggunakan Dijkstra
    std::vector<int> shortest_path = findShortestPathDijkstra(maze_graph, start_node_id, end_node_id);

    if (shortest_path.empty()) {
        std::cout << "Tidak ada jalur ditemukan dari posisi awal ke keluar." << std::endl;
        // Anda bisa memutuskan apakah game tetap berjalan atau tidak
    } else {
        std::cout << "Jalur terpendek ditemukan dengan " << shortest_path.size() << " langkah." << std::endl;
    }

    // Render awal pemain dan maze (termasuk path jika ditemukan)
    // Perhatikan urutan argumen untuk showPlayerPos yang sudah diperbaiki
    showPlayerPos(player_row_pos, player_col_pos);
    renderMaze(player_row_pos, player_col_pos, maze, shortest_path, num_cols);


    // Game loop utama
    while (true)
    {
        char key_input = getch(); // Menggunakan nama variabel yang berbeda

        if (key_input == 0 || key_input == -32) // Prefix untuk arrow keys
        {
            key_input = getch(); // Kode aktual arrow key
            int new_row = player_row_pos;
            int new_col = player_col_pos;

            switch (key_input)
            {
            case KEY_UP:
                new_row--;
                break;
            case KEY_DOWN:
                new_row++;
                break;
            case KEY_LEFT:
                new_col--;
                break;
            case KEY_RIGHT:
                new_col++;
                break;
            default:
                continue; // Abaikan input lain dari arrow key sequence
            }

            if (isPlayerMoveValid(new_row, new_col, maze)) //
            {
                player_row_pos = new_row;
                player_col_pos = new_col;

                // Cek apakah pemain mencapai jalan keluar
                if (isCompleted(player_row_pos, player_col_pos, maze_exit_row, maze_exit_col))
                {
                    clearScreen();
                    int inp;

                    std::cout << "Selamat anda telah menyelesaikan labirin ini! \n";
                    std::cout << "Berikut hadiah untuk anda: \xF0\x9F\x8E\x81 \n"; // Emoji kado (UTF-8)
                    std::cout << "[1] Ulang \n";
                    std::cout << "[2] Selesai \n";
                    std::cout << "> ";
                    std::cin >> inp;

                    // Membersihkan buffer input setelah std::cin
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                    if (inp == 1)
                    {
                        std::cout << "Mengulang kembali...\n";
                        // Reset posisi pemain
                        player_row_pos = 0; // Atau posisi awal yang ditentukan
                        player_col_pos = 1;

                        // Hitung ulang path jika diperlukan (misalnya jika maze berubah atau hanya untuk tampilan)
                        // start_node_id = player_row_pos * num_cols + player_col_pos;
                        // shortest_path = findShortestPathDijkstra(maze_graph, start_node_id, end_node_id);


                        clearScreen();
                        showPlayerPos(player_row_pos, player_col_pos);
                        renderMaze(player_row_pos, player_col_pos, maze, shortest_path, num_cols);
                    }
                    else if (inp == 2)
                    {
                        std::cout << "Program telah selesai.\n";
                        break; // Keluar dari while loop
                    }
                    else
                    {
                        std::cout << "Input tidak valid!\n";
                        std::cout << "Memberhentikan program...\n";
                        break; // Keluar dari while loop
                    }
                }
                else
                {
                    // showPlayerPos sudah memanggil clearScreen
                    showPlayerPos(player_row_pos, player_col_pos);
                    renderMaze(player_row_pos, player_col_pos, maze, shortest_path, num_cols);
                }
            }
        } else if (key_input == 'q' || key_input == 'Q') { // Tambahkan opsi keluar
            std::cout << "Program dihentikan oleh pengguna." << std::endl;
            break;
        }
    }

    return 0;
}