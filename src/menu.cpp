#include <iostream>
#include "../include/clear_screen.h"
#include "../include/menu.h"
#include "../include/login.h"

using namespace std;

void showTitle() {
    cout << "==============================" << endl;
    cout << "      WELCOME TO ALGOMAZE     " << endl;
    cout << "==============================" << endl;
}

void showMainMenu() {
    cout << "1. Play Game\n";
    cout << "2. Logout\n";
    cout << "3. Quit\n";
}


int mainMenu() {
    int choice;

    while (true) {     
        clearScreen();    
        showTitle();           
        showMainMenu();       
        cin >> choice;

        switch (choice) {
            case 1:
                cin.ignore();
                clearScreen(); 
                return true;
            case 2:
                cin.ignore();
                cout << "\nAnda telah logout dari Algomaze.\n";
                clearScreen();
                menuLoginorRegister();
                break;
            case 3:
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