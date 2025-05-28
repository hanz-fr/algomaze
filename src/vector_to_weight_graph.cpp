#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;

struct Edge
{
    // from, to, weight
    // int u, v, w;
    pair<int, int> u;
    pair<int, int> v;
    int w;
};

struct Graph
{
    // vertices, edges
    int V, E;
    // Edge *edge;
    vector<pair<int, int>> vertices;
    vector<Edge> edges;
};

int countNeighbors (int r, int c, const vector<vector<bool>>& maze_data) {
    int rows = maze_data.size();
    int cols = maze_data[0].size();
    int count = 0;

    if (r - 1 >= 0 && !maze_data[r - 1][c]) count++; // up
    if (r + 1 < rows && !maze_data[r + 1][c]) count++; // down
    if (c - 1 >= 0 && !maze_data[r][c - 1]) count++; // left
    if (c + 1 < cols && !maze_data[r][c + 1]) count++; // right

    return count;
}

bool isWeight (int r, int c, const vector<vector<bool>>& maze_data) {
    int rows = maze_data.size();
    int cols = maze_data[0].size();
    
    // horizontal weight:
    if (r-1 >= 0 && r+1 < rows && (maze_data[r-1][c] && maze_data[r+1][c]) && (!maze_data[r][c-1] && !maze_data[r][c+1])) {
        return true;
    }
    // vertical weight:
    if (c-1 >= 0 && c+1 < cols && (!maze_data[r-1][c] && !maze_data[r+1][c]) && (maze_data[r][c-1] && maze_data[r][c+1])) {
        return true;
    }

    return false;
}

Graph buildGraph (const vector<vector<bool>>& maze_data) {
    Graph graph;

    int rows = maze_data.size();
    int cols = maze_data[0].size();

    graph.V = 0;

    // fetch maze
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // if element is 0 AND (neighbor != 2 OR not a weight)
            if (!maze_data[r][c]) {
                // check if not a weight
                int neighbors = countNeighbors(r, c, maze_data);
                if (neighbors != 2 || !isWeight(r, c, maze_data)) {
                    // below here is node
                    pair<int, int> u = {r, c};
                    pair<int, int> w = {0, 0};

                    // check has right and bottom neighbor
                    while (c-1 >= 0 && c+1 < cols && !maze_data[r][c+w.second+1] && isWeight(r, c+w.second+1, maze_data)) {
                        ++w.second;
                    }
                    while (r-1 >= 0 && r+1 < rows && !maze_data[r+w.first+1][c] && isWeight(r+w.first+1, c, maze_data)) {
                        ++w.first;
                    }

                    // only add edge if it the neighbor is 0
                    // horizontal edge
                    if (c-1 >= 0 && c+1 < cols && !maze_data[r][c+1]) {
                        graph.edges.push_back({u, {r, c + w.second + 1}, w.second + 1});
                    }
                    // vertical edge
                    if (r-1 >= 0 && r+1 < rows && !maze_data[r+1][c]) {
                        graph.edges.push_back({u, {r + w.first + 1, c}, w.first + 1});
                    }       

                    graph.vertices.push_back({u});

                    ++graph.V;             
                }
            }
        }
    }

    graph.E = graph.edges.size();

    return graph;
}

int main () {   
    vector<vector<bool>> maze = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    for (const auto& row : maze) {
        for (bool cell : row) {
            cout << (cell ? "1" : "0");
        }
        cout << '\n';
    }

    Graph graph = buildGraph(maze);

    cout << "Graph:" << endl;
    cout << "Vertices: " << graph.V << endl;
    cout << "Edges: " << graph.E << endl << endl;

    cout << "Vertices: " << endl;
    for (int i = 0; i < graph.V; ++i) {
        cout << "[" << graph.vertices[i].first << "][" << graph.vertices[i].second << "]" << endl; 
    }
    cout << endl;

    cout << "Edges (U,V,W): " << endl;
    for (int i = 0; i < graph.E; ++i) {
        cout << "[" << graph.edges[i].u.first << "][" << graph.edges[i].u.second << "] ";
        cout << "[" << graph.edges[i].v.first << "][" << graph.edges[i].v.second << "] ";
        cout << "Weight: " << graph.edges[i].w << endl; 
    }
    cout << endl;

    return 0;
}