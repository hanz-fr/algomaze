#include "../include/maze.h"
#include "../include/render_maze.h"
#include "../include/clear_screen.h"
#include "../include/keyinp.h"
#include "../include/player_pos.h" 
#include "../include/graph.h"
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <vector>

int main()
{
    // Buat maze dari file maze
    std::vector<std::vector<bool>> game_maze = createMaze();
    if (game_maze.empty() || game_maze[0].empty()) 
    {
        std::cerr << "Error: Gagal membuat maze atau maze kosong." << std::endl;
        return 1;
    }

    // Bangun graph dari maze
    std::map<int, std::vector<int>> maze_graph = buildGraph(game_maze);

    // Inisialisasi posisi pemain
    player_row_pos = 0; // Baris awal
    player_col_pos = 1; // Kolom awal

    if (player_row_pos >= game_maze.size() || player_col_pos >= game_maze[0].size() || !game_maze[player_row_pos][player_col_pos]) 
    {
        std::cerr << "Error: Posisi pemain di luar batas maze." << std::endl;
    }

    clearScreen();
    renderMaze(game_maze, player_row_pos, player_col_pos);
    printRowCol(player_row_pos, player_col_pos);

    int c = 0;

    while (true)
    {
        c = getch();

        int prev_player_row_pos = player_row_pos;
        int prev_player_col_pos = player_col_pos;

        if (c == 0 || c == 224)
        {
            c = getch();
            switch (c)
            {
            case KEY_UP:
                // clearScreen();
                player_row_pos = moveUp(player_row_pos);
                break;
            case KEY_DOWN:
                // clearScreen();
                player_row_pos = moveDown(player_row_pos);
                break;
            case KEY_LEFT:
                // clearScreen();
                player_col_pos = moveLeft(player_col_pos);
                break;
            case KEY_RIGHT:
                // clearScreen();
                player_col_pos = moveRight(player_col_pos);
                break;
            default:
                std::cout << "Unknown special key: " << c << std::endl;
                break;
            }
        }
        else if (c == 27) // ESC key
        {
            std::cout << "ESC key pressed. Exiting..." << std::endl;
            break;
        }
        else
        {
            std::cout << "Not an arrow key." << std::endl;
        }

        // Tabrakan posisi pemain dengan maze
        bool moved = true;
        if (player_row_pos < 0 || player_row_pos >= game_maze.size() ||
             player_col_pos < 0 || player_col_pos >= game_maze[0].size() || 
             game_maze[player_row_pos][player_col_pos])
        {
            player_row_pos = prev_player_row_pos;
            player_col_pos = prev_player_col_pos;
            moved = false;
        }
        if(moved || c == 0 || c == 224)
        {
            renderMaze(game_maze, player_row_pos, player_col_pos);
            printRowCol(player_row_pos, player_col_pos);
        }
    }

    return 0;
}