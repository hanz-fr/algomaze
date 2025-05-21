#include "../include/render_maze.h"
#include "../include/clear_screen.h"
#include "../include/keyinp.h"
#include "../include/player_pos.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>

int main()
{
    int c = 0;

    while (1)
    {
        c = getch();

        if (c == 0 || c == 224)
        {
            c = getch();
            switch (c)
            {
            case KEY_UP:
                clearScreen();
                player_row_pos = moveUp(player_row_pos);
                renderMaze(player_col_pos, player_row_pos);
                break;
            case KEY_DOWN:
                clearScreen();
                player_row_pos = moveDown(player_row_pos);
                renderMaze(player_col_pos, player_row_pos);
                break;
            case KEY_LEFT:
                clearScreen();
                player_col_pos = moveLeft(player_col_pos);
                renderMaze(player_col_pos, player_row_pos);
                break;
            case KEY_RIGHT:
                clearScreen();
                player_col_pos = moveRight(player_col_pos);
                renderMaze(player_col_pos, player_row_pos);
                break;
            default:
                std::cout << "Unknown special key: " << c << std::endl;
                break;
            }
        }
        else
        {
            std::cout << "Not an arrow key." << std::endl;
        }
    }

    return 0;
}