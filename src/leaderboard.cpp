#include "leaderboard.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "../include/clear_screen.h"

using namespace std;

void saveToLeaderboard(const string& username, double time) 
{
    ifstream maze("database/currentMaze.txt");
    string mazeId;

    if (maze.is_open()) {
        if (maze.is_open()) {
            getline(maze, mazeId);
            maze.close();
        }
        else {
            cerr << "Gagal membuka file id.txt\n";
            return;
        }
    }

    ofstream file("database/leaderboard.txt", ios::app);
    if (file.is_open()) {
        file << mazeId << "|" << username << " " << time << "\n";
        file.close();
    } else {
        cerr << "Gagal membuka file leaderboard.txt untuk menulis\n";
    }
}

void showLeaderboard() {
    ifstream file("database/leaderboard.txt");
    ifstream maze("database/currentMaze.txt");
    vector<pair<string, double>> records;
    string mazeId;

    if (maze.is_open()) {
        if (maze.is_open()) {
            getline(maze, mazeId);
            maze.close();
        }
        else {
            cerr << "Gagal membuka file id.txt\n";
            return;
        }
    }

    if (file.is_open()) {
        string row;
        while (getline(file, row)) {
            size_t pos = row.find("|");
            if (pos == string::npos) continue;

            string id = row.substr(0, pos);
            string name_time = row.substr(pos + 1);

            if (id != mazeId) continue; // current maze

            istringstream iss(name_time);
            string name;
            double time;

            if (iss >> name >> time) 
            {
                records.push_back({name, time});
            }
        }
        file.close();
    }
    else {
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
