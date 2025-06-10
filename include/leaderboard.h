#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <string>

void saveToLeaderboard(const std::string& username, double time);
void showLeaderboard();

#endif