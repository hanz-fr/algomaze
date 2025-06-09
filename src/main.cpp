#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include "../include/player_movement.h"
#include "../include/keyinp.h"
#include "../include/clear_screen.h"
#include "../include/render_maze.h"
#include "../include/maze.h"
#include "../include/player_pos.h"
#include "../include/vector_to_graph.h"
#include "../include/maze_completed.h"
#include "../include/welcome_press_any_key.h"
#include "../include/login.h"
#include "../include/help_dijkstra.h"
#include "../include/menu.h"
#include "../include/timer.h"
#include "../include/leaderboard.h"

int main () {
    std::string welcome_message = "Welcome to the Algorithm Maze Game!";
    std::string author = "Made by group 4";
    std::string press_key_to_continue = "Press any key to continue...";

    animateText(welcome_message, 75);
    animateText(author, 75);
    blinkTextUntilKeyPress(press_key_to_continue, 400);
    clearScreen();

    // initiate login/register menu
    menuLoginorRegister();
    mainMenu();
    
    return 0;
}

int game ()
{
    int c = 0;

    // player starting position
    int player_row_pos = 0;
    int player_col_pos = 1;

    // maze finish position
    int maze_exit_row = 24;
    int maze_exit_col = 16;

    std::vector<std::vector<bool>> maze = initiateMaze();          // first maze initialization
    std::map<int, std::vector<int>> maze_graph = buildGraph(maze); // convert to graph (adjacency matrix)

    startTimer(); //mulai waktunya //perubahan

    // initial render of player and maze
    showPlayerPos(player_row_pos, player_col_pos);
    renderMaze(player_row_pos, player_col_pos, maze);

    while (true)
    {
        char c = getch();
        
        if (c == 27 ) {
            std::cout << "ESC pressed, exiting...\n";
            clearScreen();
            mainMenu();
            return 0;
        }

        if (c == 0 || c == -32)
        {
            c = getch();
            int new_row = player_row_pos;
            int new_col = player_col_pos;

            switch (c)
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
            }

            if (isPlayerMoveValid(new_row, new_col, maze))
            {
                player_row_pos = new_row;
                player_col_pos = new_col;

                // only render when move is valid
                // show congrats when maze completed
                if (isCompleted(player_row_pos, player_col_pos, maze))
                {
                    clearScreen();

                    double time = stopTimer(); //perubahan 
                    std::string username;
                    {
                        std::ifstream sessionFile("database/loginSession.txt");
                        if (sessionFile.is_open()) 
                        {
                            std::getline(sessionFile, username);
                            sessionFile.close();
                        } else {
                            username = "Unknown";
                        }
                    }

                    saveToLeaderboard(username, time);
                    std::cout << "Waktu penyelesaian: " << time << "detik";
                    int inp;

                    std::cout << "Selamat anda telah menyelesaikan labirin ini! \n";
                    std::cout << "Berikut hadiah untuk anda: 🎁 \n";
                    std::cout << "[1] Ulang \n";
                    std::cout << "[2] Liat rangking \n";
                    std::cout << "[3] Keluar \n";
                    std::cout << "> ";
                    std::cin >> inp;

                    if (inp == 1)
                    {
                        std::cout << "Mengulang kembali...";

                        player_row_pos = 0;
                        player_col_pos = 1;

                        clearScreen();
                        startTimer();
                        showPlayerPos(player_row_pos, player_col_pos);
                        renderMaze(player_row_pos, player_col_pos, maze);
                    }
                    else if (inp == 2)
                    {
                        showLeaderboard();

                        std::cout << "Tekan ENTER untuk kembali ke menu...";
                        std::cin.ignore();
                        std::cin.get();
                        mainMenu();
                        return 0;
                    }
                    else if (inp == 3)
                    {
                        mainMenu();
                        return 0;
                    }
                    else
                    {
                        std::cout << "Input tidak valid!\n";
                        std::cout << "Memberhentikan program...\n";
                        break;
                    }
                }
                else
                {
                    clearScreen();
                    showPlayerPos(player_row_pos, player_col_pos);
                    renderMaze(player_row_pos, player_col_pos, maze);
                    std::cout << "\nButuh bantuan? Tekan H untuk meminta bantuan.\n";
                }
            }
        
        }
        else if ( c == 'h' || c == 'H')
        {
            showHelpDijkstra(player_row_pos, player_col_pos, maze_exit_row, maze_exit_col, maze, maze_graph);
        }
        else if (c == 'q' || c == 'Q')
        {
            std::cout << "Program telah selesai.\n";
            break;
        }
    }

    return 0;
}

