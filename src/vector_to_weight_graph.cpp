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
    pair <int, int> weight = {0,0};
};

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

Graph buildGraph (const vector<vector<bool>>& maze_data) {
    vector<Element> elements; 
    Graph graph;

    int rows = maze_data.size();
    int cols = maze_data[0].size();
    
    int vertices = 0;
    
    // fetch maze
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // if element is 0
            if (!maze_data[r][c]) {
                Element element;
                element.position = {r, c};
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
                                elements[j].weight.second++;
                                break;
                            }
                        }
                    }
                    // is vertical weight
                    else if (r - 1 >= 0 && r + 1 < rows && !maze_data[r - 1][c] && !maze_data[r + 1][c]) {
                        element.type = "vertical";
                        for (int j = elements.size() - 1; j >= 0; --j) {
                            if (elements[j].position.second == c && elements[j].type == "node") {
                                elements[j].weight.first++;
                                break;
                            }
                        }
                    }
                }
                // put element to elements vector
                elements.push_back(element);
            }
        }
    }

    // LAST STEP
    // fetch nodes
    for (int i = 0; i < elements.size(); ++i) {
        if (elements[i].type == "node") {
            pair<int, int> u = elements[i].position;
            pair<int, int> w = elements[i].weight;

            // each node do:
            // how would it know if its a node without fetching?
            // ^^ all node is already defined, so there wouldnt be a weight by mistake, just need to check if its a 0 or 1 element using maze matrix index
            
            // CREATE EDGE
            // horizontal: [r][c + weight.col + 1]
            if (u.second + w.second + 1 < cols && maze_data[u.first][u.second + w.second + 1] == 0) {
                graph.edges.push_back({u, {u.first, u.second + w.second + 1}, w.second + 1}); // w only (on 3rd param) without +1 means adjacent vertex will weigh 0
            }

            // vertical: [r + weight.row + 1][c]
            if (u.first + w.first + 1 < rows && maze_data[u.first + w.first + 1][u.second] == 0) {
                graph.edges.push_back({u, {u.first + w.first + 1, u.second}, w.first + 1}); // this too
            }
            graph.vertices.push_back(u);
            ++vertices;
        }
    }
    graph.V = vertices;
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