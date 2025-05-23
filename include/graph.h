#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map> 

// menyimpan informasi node dalam maze 
struct Node {
    int id;
    int row;
    int col;
};

// Fungsi untuk membangun adjacency list dari data maze
// (Asumsi 0 = jalur, 1 = tembok)
std::map<int, std::vector<int>> buildGraph(const std::vector<std::vector<bool>>& maze_data);

#endif