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

int main()
{
    int c = 0;

    // posisi start player
    int player_row_pos = 1;
    int player_col_pos = 0;

    std::vector<std::vector<bool>> maze = initiateMaze(); // inisialisasi maze awal
    std::map<int, std::vector<int>> maze_graph = buildGraph(maze);

    showPlayerPos(player_col_pos, player_row_pos);
    renderMaze(player_row_pos, player_col_pos, maze);

    if (player_row_pos >= maze.size() || player_col_pos >= maze[0].size() || !maze[player_row_pos][player_col_pos]) 
    {
        std::cerr << "Error: Posisi pemain di luar batas maze." << std::endl;
    }
    while (true) {
        char c = getch();

        if (c == 0 || c == -32) {
            c = getch();
            int new_row = player_row_pos;
            int new_col = player_col_pos;

            switch (c) {
                case KEY_UP:    new_col--; break;
                case KEY_DOWN:  new_col++; break;
                case KEY_LEFT:  new_row--; break;
                case KEY_RIGHT: new_row++; break;
            }

            if (isPlayerMoveValid(new_row, new_col, maze)) {
                player_row_pos = new_row;
                player_col_pos = new_col;

                // render is now moved to only when move is valid
                clearScreen();
                showPlayerPos(player_col_pos, player_row_pos);
                renderMaze(player_row_pos, player_col_pos, maze);
            }
        }
    }

    return 0;
}