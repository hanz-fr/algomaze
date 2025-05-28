#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;

struct Edge
{
    // from, to, weight
    pair<int, int> u;
    pair<int, int> v;
    int w;
};

struct Graph
{
    // vertices, edges
    int V, E;;
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

    // check if in bounds before checking weight
    if (r - 1 >= 0 && r + 1 < rows && c - 1 >= 0 && c + 1 < cols) {
        // horizontal weight
        if (maze_data[r - 1][c] && maze_data[r + 1][c] &&       // vertical is 1
            !maze_data[r][c - 1] && !maze_data[r][c + 1]) {     // horizontal is 0
            return true;
        }

        // vertical weight
        if (!maze_data[r - 1][c] && !maze_data[r + 1][c] &&     // vertical is 0 
            maze_data[r][c - 1] && maze_data[r][c + 1]) {       // horizontal is 1
            return true;
        }
    }

    return false;
}

Graph buildGraph (const vector<vector<bool>>& maze_data) {
    Graph graph;

    int rows = maze_data.size();
    int cols = maze_data[0].size();

    // fetch maze
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // maze elements that are 0
            if (!maze_data[r][c]) {
                int neighbors = countNeighbors(r, c, maze_data);
                
                // filter out weight elements, so we're only left with nodes
                if (neighbors != 2 || !isWeight(r, c, maze_data)) {
                    pair<int, int> u = {r, c};
                    pair<int, int> w = {0, 0};

                    // add weights to current node
                    // horizontal stretch (right)
                    while (c + w.second + 1 < cols &&                   // make sure not out of bounds
                        !maze_data[r][c + w.second + 1] &&              // is 0
                        isWeight(r, c + w.second + 1, maze_data)) {     // is weight
                        ++w.second;
                    }

                    // vertical stretch (down)
                    while (r + w.first + 1 < rows &&                    // make sure not out of bounds
                        !maze_data[r + w.first + 1][c] &&               // is 0
                        isWeight(r + w.first + 1, c, maze_data)) {      // is weight
                        ++w.first;
                    }

                    // create horizontal edge
                    if (c + w.second + 1 < cols && !maze_data[r][c + w.second + 1]) {
                        graph.edges.push_back({u, {r, c + w.second + 1}, w.second + 1});
                    }

                    // create vertical edge
                    if (r + w.first + 1 < rows && !maze_data[r + w.first + 1][c]) {
                        graph.edges.push_back({u, {r + w.first + 1, c}, w.first + 1});
                    }

                    // add current node to nodes vector
                    graph.vertices.push_back({u});
                }
            }
        }
    }

    graph.V = graph.vertices.size();
    graph.E = graph.edges.size();

    return graph;
}

int main () {   
    vector<vector<bool>> maze = {
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    for (const auto& row : maze) {
        for (bool cell : row) {
            cout << (cell ? char(219) : ' ');
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