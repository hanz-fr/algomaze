#include "leaderboard.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "../include/clear_screen.h"

using namespace std;

void saveToLeaderboard(const string& username, double time) 
{
    ofstream file("database/leaderboard.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << time << "\n";
        file.close();
    } else {
        cerr << "Gagal membuka file leaderboard.txt untuk menulis\n";
    }
}

void showLeaderboard() {
    ifstream file("database/leaderboard.txt");
    vector<pair<string, double>> records;

    if (file.is_open()) 
    {
        string name;
        double time;
        while (file >> name >> time) {
            records.push_back({name, time});
        }
        file.close();
    } else {
        cerr << "Gagal membuka file leaderboard.txt untuk membaca\n";
        return;
    }

    sort(records.begin(), records.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });

    clearScreen();
    cout << "==============================" << endl;
    cout << "          LEADERBOARD         " << endl;
    cout << "==============================" << endl;
    size_t topN = min(records.size(), size_t(5));

    for (size_t i = 0; i < topN; ++i) 
    {
        cout << i + 1 << ". " << records[i].first << " - " << fixed << setprecision(2) << records[i].second << " detik\n";
    }
    cout << "==============================\n\n";
}
