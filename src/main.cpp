#include <stdio.h>
#include <iostream>
#include <conio.h>
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
#include "../include/menu.h"

int main()
{
    int c = 0;

    std::string welcome_message = "Welcome to the Algorithm Maze Game!";
    std::string author = "Made by group 4";
    std::string press_key_to_continue = "Press any key to continue...";

    animateText(welcome_message, 75);
    animateText(author, 75);
    blinkTextUntilKeyPress(press_key_to_continue, 400);
    clearScreen();

    // initiate login/register menu
    menuLoginorRegister();

    // initiate menu
    if (mainMenu() == -1){
        return 0;
    }


    // player starting position
    int player_row_pos = 0;
    int player_col_pos = 1;

    // maze finish position
    int maze_exit_row = 25;
    int maze_exit_col = 16;

    std::vector<std::vector<bool>> maze = initiateMaze();          // first maze initialization
    std::map<int, std::vector<int>> maze_graph = buildGraph(maze); // convert to graph (adjacency matrix)

    // initial render of player and maze
    showPlayerPos(player_row_pos, player_col_pos);
    renderMaze(player_row_pos, player_col_pos, maze);

    while (true)
    {
        char c = getch();

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
                    int inp;

                    std::cout << "Selamat anda telah menyelesaikan labirin ini! \n";
                    std::cout << "Berikut hadiah untuk anda: 🎁 \n";
                    std::cout << "[1] Ulang \n";
                    std::cout << "[2] Selesai \n";
                    std::cout << "> ";
                    std::cin >> inp;

                    if (inp == 1)
                    {
                        std::cout << "Mengulang kembali...";

                        player_row_pos = 0;
                        player_col_pos = 1;

                        clearScreen();
                        showPlayerPos(player_row_pos, player_col_pos);
                        renderMaze(player_row_pos, player_col_pos, maze);
                    }
                    else if (inp == 2)
                    {
                        std::cout << "Program telah selesai.";
                        mainMenu();
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
                }
            }
        }
    }

    return 0;
}

