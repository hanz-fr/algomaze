#include <iostream>
#include <vector>
#include <map>
#include <conio.h> 
#include <limits> 


#include "../include/player_movement.h"
#include "../include/keyinp.h"
#include "../include/clear_screen.h"
#include "../include/render_maze.h"
#include "../include/maze.h"
#include "../include/player_pos.h"
#include "../include/vector_to_graph.h"
#include "../include/dijkstra.h"


int main()
{
    // Inisialisasi maze
    std::vector<std::vector<bool>> maze = initiateMaze();
    if (maze.empty() || maze[0].empty()) {
        std::cerr << "Error: Maze tidak berhasil diinisialisasi atau kosong." << std::endl;
        return 1;
    }
    
    int num_rows = maze.size();
    int num_cols = maze[0].size();

    std::map<int, std::vector<int>> maze_graph = buildGraph(maze); 

    // Posisi awal pemain (pastikan ini adalah jalur yang valid: maze[row][col] == false)
    int player_row_pos = 0; 
    int player_col_pos = 1; 

    // Posisi keluar labirin (pastikan ini adalah jalur yang valid dan dalam batas)
    int maze_exit_row = 24; 
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

    if (shortest_path.empty() && !(start_node_id == end_node_id) ) { 
        std::cout << "Tidak ada jalur ditemukan dari posisi awal ke keluar." << std::endl;
        
        // std::this_thread::sleep_for(std::chrono::seconds(2)); // Contoh jika ingin ada delay
    } else if (!shortest_path.empty()) {
        std::cout << "Jalur terpendek ditemukan dengan " << shortest_path.size() -1 << " langkah." << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(2)); // Contoh jika ingin ada delay
    }


    // Render awal pemain dan maze 
    showPlayerPos(player_row_pos, player_col_pos); 
    renderMaze(player_row_pos, player_col_pos, maze, shortest_path, num_cols);

   
    while (true)
    {
        char key_input = getch(); 

        if (key_input == 0 || key_input == 0xE0 || key_input == -32)
        {
            key_input = getch(); 
            int new_row = player_row_pos;
            int new_col = player_col_pos;

            switch (key_input)
            {
            case KEY_UP:    new_row--; break;
            case KEY_DOWN:  new_row++; break;
            case KEY_LEFT:  new_col--; break;
            case KEY_RIGHT: new_col++; break;
            default:        continue; 
            }

            if (isPlayerMoveValid(new_row, new_col, maze))
            {
                player_row_pos = new_row;
                player_col_pos = new_col;

                // Cek apakah pemain mencapai jalan keluar
                if (player_row_pos == maze_exit_row && player_col_pos == maze_exit_col)
                {
                    // Langkah 1: menampilkan keadaan menang terakhir kali.
                    showPlayerPos(player_row_pos, player_col_pos); 
                    renderMaze(player_row_pos, player_col_pos, maze, shortest_path, num_cols);

                    // Langkah 2: Tampilkan pesan kemenangan & hadiah di layar yang sama, lalu tunggu input.
                    std::cout << "\n\nSelamat anda telah menyelesaikan labirin ini! \n";
                    std::cout << "Berikut hadiah untuk anda: scoree +100 \n";
                    std::cout << "Tekan tombol apa saja untuk melanjutkan...";
                    
                    int final_key_press = getch(); 
                    if (final_key_press == 0 || final_key_press == 0xE0 || final_key_press == -32) { 
                        getch(); 
                    }

                    // Langkah 3: menampilkan menu untuk Ulang atau Selesai.
                    clearScreen(); 
                    
                    std::cout << "[1] Ulang \n";
                    std::cout << "[2] Selesai \n";
                    std::cout << "> ";
                    
                    int inp;
                    std::cin >> inp;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                    if (inp == 1)
                    {
                        player_row_pos = 0; 
                        player_col_pos = 1;

                        showPlayerPos(player_row_pos, player_col_pos);
                        renderMaze(player_row_pos, player_col_pos, maze, shortest_path, num_cols);
                    }
                    else if (inp == 2)
                    {
                        std::cout << "Program telah selesai.\n";
                        break; 
                    }
                    else
                    {
                        std::cout << "Input tidak valid!\n";
                        std::cout << "Memberhentikan program...\n";
                        break; 
                    }
                }
                else // Jika belum menang, render maze seperti biasa.
                {
                    showPlayerPos(player_row_pos, player_col_pos);
                    renderMaze(player_row_pos, player_col_pos, maze, shortest_path, num_cols);
                }
            }
            
        } else if (key_input == 'q' || key_input == 'Q') {
            std::cout << "Program dihentikan oleh pengguna." << std::endl;
            break;
        }
    }

    return 0;
}