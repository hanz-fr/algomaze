#include "../include/clear_screen.h"
#include "../include/player_pos.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

struct History {
    int top = -1;
    vector<pair<int, int>> data;
};

History history;

void push (pair<int, int> data) {
    // if data is not the same as top-1.data
    if (history.top == -1 || history.data[history.top-1] != data) {
        history.top++;
        history.data[history.top] = data;
    }
    // else remove top
    else {
        pop();
    }
}

void pop () {
    if (!history.top == -1) {
        history.top--;
    }
}

void showPlayerPos(int row_pos, int col_pos)
{
    pair<int, int> pos = {row_pos, col_pos};
    clearScreen();

    cout << "Position: [" << pos.first << "][" << pos.second << "]" << endl;
    cout << "History: ";
    for (int i = history.top; i >= 0; i--) {
        cout << "[" << history.data[i].first << "][" << history.data[i].second << "]" << endl;
    }
}