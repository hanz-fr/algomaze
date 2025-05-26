#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;

struct Element
{
    int id;
    pair<int, int> position;
    string type;
    int weight = 0;
};

struct Edge
{
    // from, to, weight
    int u, v, w;
};

struct Graph
{
    // vertices, edges
    int V, E;
    Edge *edge;
};

Graph *createGraph (int V, int E) {
    Graph *graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];

    return graph;
}

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

map<int, vector<int>> buildGraph (const vector<vector<bool>>& maze_data) {
    vector<Element> elements; 
    map<int, vector<int>> graph;
    int id = 0;
    
    int rows = maze_data.size();
    int cols = maze_data[0].size();
    
    // fetch maze
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // if element is 0
            if (!maze_data[r][c]) {
                Element element;
                element.position = {r, c};
                element.id = id;
                element.type = "node";
                
                int neighbors = countNeighbors(r, c, maze_data);
                if (neighbors == 2) {
                    // is horizontal weight
                    if (c - 1 >= 0 && c + 1 < cols && !maze_data[r][c - 1] && !maze_data[r][c + 1]) {
                        element.type = "horizontal";
                        // [r][c--]
                        // if in elements: same row, less col
                        for (int j = elements.size() - 1; j >= 0; --j) {
                            if (elements[j].position.first == r && elements[j].type == "node") {
                                elements[j].weight++;
                                break;
                            }
                        }
                    }
                    // is vertical weight
                    else if (r - 1 >= 0 && r + 1 < rows && !maze_data[r - 1][c] && !maze_data[r + 1][c]) {
                        element.type = "vertical";
                        for (int j = elements.size() - 1; j >= 0; --j) {
                            if (elements[j].position.second == c && elements[j].type == "node") {
                                elements[j].weight++;
                                break;
                            }
                        }
                    }
                }
                // put element to elements vector
                elements.push_back(element);
                ++id;
            }
        }
    }

    // fetch vector
    for (int i = 0; i < elements.size(); ++i) {
        cout << "["<< elements[i].position.first << "]" << "["<< elements[i].position.second << "] is a " << elements[i].type;
        if (elements[i].type == "node") {
            cout << " has weight: " << elements[i].weight;
        }
        cout << endl;
    }

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
            cout << (cell ? "1" : "0");
        }
        cout << '\n';
    }

    map<int, vector<int>> graph = buildGraph(maze);
    return 0;
}