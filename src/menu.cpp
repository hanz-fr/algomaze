#include <iostream>
#include <windows.h>
#include <filesystem>
#include "../include/clear_screen.h"
#include "../include/menu.h"
#include "../include/main.h"
#include "../include/login.h"
#include "../include/welcome_press_any_key.h"
#include "../include/leaderboard.h"
#include "../include/game.h"

using namespace std;

std::filesystem::path cwd = std::filesystem::current_path(); // Get current working directory
std::filesystem::path draw_maze_execute_command = cwd / "build" / "draw_maze.exe"; // command to execute draw_maze
std::filesystem::path choose_maze_execute_command = cwd / "build" / "choose_maze.exe"; // command to execute choose_maze
std::string draw_maze_path = "\"" + draw_maze_execute_command.string() + "\"";
std::string choose_maze_path = "\"" + choose_maze_execute_command.string() + "\"";

void showTitle()
{
    cout << "==============================" << endl;
    cout << "      WELCOME TO ALGOMAZE     " << endl;
    cout << "==============================" << endl;
}

void showMainMenu()
{
    cout << "1. Play Game\n";
    cout << "2. Mode Tantangan\n";
    cout << "3. Leaderboard\n";
    cout << "4. Pilih Maze\n";
    cout << "5. Gambar Maze\n";
    cout << "6. Logout\n";
    cout << "7. Quit\n";
    cout << "==============================\n\n";
}

int mainMenu()
{
    int choice;

    while (true)
    {
        clearScreen();
        showTitle();
        showMainMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cin.ignore();
            clearScreen();
            game(false);
            break;
        case 2:
            cin.ignore();
            clearScreen();
            game(true);
            break;
        case 3:
            showLeaderboard();
            std::cout << "Tekan ENTER untuk kembali ke menu...";
            std::cin.ignore();
            std::cin.get();
            mainMenu();
            return 0;
        case 4:
            system(choose_maze_path.c_str());
            mainMenu();
            break;
        case 5:
            system(draw_maze_path.c_str());
            mainMenu();
            return 0;
        case 6:
            cin.ignore();
            cout << "\nAnda telah logout dari Algomaze.\n";
            clearScreen();
            menuLoginorRegister();
            break;
        case 7:
            cout << "\nTerima kasih telah bermain Algomaze!\n";
            return -1;
        default:
            cout << "\nPilihan tidak valid. Coba lagi.\n";
            cout << "Tekan Enter untuk lanjut...";
            cin.ignore();
            cin.get();
            break;
        }
    }

    return 0;
}