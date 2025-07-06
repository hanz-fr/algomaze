#include "../include/game.h"
#include "../include/timer.h"          
#include "../include/countdown.h"       
#include "../include/maze.h"
#include "../include/read_maze_from_db.h"
#include "../include/select_maze.h"
#include "../include/player_pos.h"
#include "../include/render_maze.h"
#include "../include/player_movement.h"
#include "../include/vector_to_graph.h"
#include "../include/help_dijkstra.h"
#include "../include/leaderboard.h"
#include "../include/keyinp.h"
#include "../include/clear_screen.h"
#include "../include/menu.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>
#include <iomanip> 
#include <thread>  
#include <chrono>  

int game(bool isChallengeMode) {
    
    int player_row_pos, player_col_pos;
    int maze_exit_row, maze_exit_col;
    std::vector<std::vector<bool>> maze;

    int currentMazeIndex = viewCurrentSelectedMaze("database/currentMaze.txt");
    
    // Kondisi kalau maze yang dipilih itu default
    if (currentMazeIndex == -1) {
        player_row_pos = 0;
        player_col_pos = 1;
        maze_exit_row = 24;
        maze_exit_col = 16;
        maze = initiateMaze();
    }
    // Kondisi kalau maze yang dipilih itu maze custom
    else {
        auto [start, end] = getCurrentMazeStartAndFinish("database/maze.txt", currentMazeIndex);
        player_row_pos = start.first;
        player_col_pos = start.second;
        maze_exit_row = end.first;
        maze_exit_col = end.second;
        maze = readMazeFromDB("database/maze.txt", currentMazeIndex);
    }

    std::map<int, std::vector<int>> maze_graph = buildGraph(maze);

    if (isChallengeMode) {
        startCountdown(60); 
    } else {
        startTimer(); 
    }

    while (true) {
        // 1. CEK KONDISI KALAH (Hanya berlaku di Mode Tantangan)
        if (isChallengeMode && isCountdownTimeUp()) {
            stopCountdown();
            clearScreen();
            std::cout << "WAKTU HABIS!\n";
            std::cout << "Anda gagal menyelesaikan labirin tepat waktu.\n\n";
            std::cout << "Tekan tombol apa saja untuk kembali ke menu utama...";
            int key = getch();
            if (key == 0 || key == -32 || key == 224) { // Menangani sisa input dari tombol panah
                getch();
            }
            break;
        }

        // 2. RENDER TAMPILAN
        clearScreen();
        showPlayerPos(player_row_pos, player_col_pos);
        if (isChallengeMode) {
            int sisa_waktu = getCountdownTimeLeft();
            std::cout << "Sisa Waktu: " << sisa_waktu / 60 << ":" 
                      << std::setw(2) << std::setfill('0') << sisa_waktu % 60 << std::endl;
        }
        renderMaze(player_row_pos, player_col_pos, maze);
        std::cout << "\nButuh bantuan? Tekan H. Tekan ESC untuk kembali ke menu.\n";
        
        // 3. PROSES INPUT PEMAIN
        char c;
        if (isChallengeMode) {
            
            if (_kbhit()){
                c = getch();
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                continue;
            }
        } else {
            
            c = getch();
        }

        // Handle ESC untuk kembali ke menu
        if (c == 27) {
            if (isChallengeMode) stopCountdown();
            
            break; 
        }

        // Handle Tombol Bantuan
        if (c == 'h' || c == 'H') {
            showHelpDijkstra(player_row_pos, player_col_pos, maze_exit_row, maze_exit_col, maze, maze_graph);
            std::cout << "\nTekan tombol apa saja untuk melanjutkan permainan...";
            getch();
            continue; 
        }
        
        // Handle Gerakan Pemain (arrow keys)
        if (c == 0 || c == -32 || c == 224) {
            c = getch();
            int new_row = player_row_pos, new_col = player_col_pos;
            switch (c) {
                case KEY_UP: new_row--; break;
                case KEY_DOWN: new_row++; break;
                case KEY_LEFT: new_col--; break;
                case KEY_RIGHT: new_col++; break;
            }

            if (isPlayerMoveValid(new_row, new_col, maze)) {
                player_row_pos = new_row;
                player_col_pos = new_col;

                // Cek Kondisi Menang
                if (player_row_pos == maze_exit_row && player_col_pos == maze_exit_col) {
                    clearScreen();
                    std::cout << "Selamat, Anda berhasil menyelesaikan labirin!\n\n";

                    if (isChallengeMode) {
                        stopCountdown();
                        int sisa_waktu = getCountdownTimeLeft();
                        std::cout << "Anda menyelesaikan dengan sisa waktu: " << sisa_waktu << " detik.\n";
                        
                    } else {
                        double time_taken = stopTimer();
                        std::string username;
                        std::ifstream sessionFile("database/loginSession.txt");
                        if (sessionFile.is_open()) { std::getline(sessionFile, username); }
                        
                        saveToLeaderboard(username, time_taken);
                        std::cout << "Waktu penyelesaian: " << std::fixed << std::setprecision(2) << time_taken << " detik.\n";
                    }

                    std::cout << "\n[1] Ulang Mode Ini\n";
                    std::cout << "[2] Kembali ke Menu Utama\n> ";
                    
                    int inp;
                    std::cin >> inp;
                    if(inp == 1) {
                         return game(isChallengeMode); 
                    } else {
                         return 0; 
                    }
                }
            }
        }
    }
    return 0; 
}