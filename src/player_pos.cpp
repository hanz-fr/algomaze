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

void pop () {
    if (history.top != -1) {
        history.top--;
    }
}

void push(pair<int, int> data) {
    // Check if user undo their last move (go back to top - 1 position)
    if (history.top >= 1 && history.data[history.top - 1] == data) {
        pop();  // remove the most recent position
    } else {
        history.top++;
        if (history.top < history.data.size()) {
            history.data[history.top] = data;
        } else {
            history.data.push_back(data);
        }
    }
}

void showPlayerPos(int row_pos, int col_pos)
{
    pair<int, int> pos = {row_pos, col_pos};
    push(pos);
    
    clearScreen();

    cout << "Position: [" << pos.first << "][" << pos.second << "]" << endl;
    cout << "History: ";
    for (int i = history.top; i >= 0; i--) {
        cout << "[" << history.data[i].first << "][" << history.data[i].second << "]";
    }
    cout << endl;
}