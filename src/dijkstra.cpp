#include "../include/dijkstra.h"
#include <queue>         
#include <map>           
#include <vector>         
#include <algorithm>      
#include <limits>         

std::vector<int> findShortestPathDijkstra(
    const std::map<int, std::vector<int>>& graph,
    int start_node_id,
    int end_node_id) {

    std::map<int, int> distances; 
    std::map<int, int> previous_nodes; 

    // untuk menyimpan {jarak, node_id}, diurutkan berdasarkan jarak terkecil
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    // Inisialisasi jarak: tak terhingga untuk semua node,
    for (const auto& pair : graph) {
        distances[pair.first] = std::numeric_limits<int>::max();
        previous_nodes[pair.first] = -1; // -1 menandakan tidak ada node sebelumnya
    }

    // Jika node awal atau akhir tidak ada dalam graph (misal, tembok)
    if (graph.find(start_node_id) == graph.end() || graph.find(end_node_id) == graph.end()) {
        return {}; 
    }

    distances[start_node_id] = 0;
    pq.push({0, start_node_id}); // Masukkan node awal ke priority queue

    while (!pq.empty()) {
        int u_dist = pq.top().first; // Jarak node teratas saat ini
        int u = pq.top().second;    // ID node teratas saat ini
        pq.pop();

        // Jika kita sudah menemukan jalur yang lebih pendek ke u, lewati
        if (u_dist > distances[u]) {
            continue;
        }

        // Jika kita mencapai node tujuan
        if (u == end_node_id) {
            std::vector<int> path;
            int current = end_node_id;

            // Rekonstruksi path dari end_node_id ke start_node_id
            while (current != -1 && current != start_node_id) {
                path.push_back(current);
                // Pastikan current ada di previous_nodes sebelum diakses
                if (previous_nodes.find(current) == previous_nodes.end()){
                    return {}; 
                }
                current = previous_nodes[current];
            }
            path.push_back(start_node_id); // Tambahkan node awal ke path
            std::reverse(path.begin(), path.end()); // Balik path agar dari awal ke akhir

            // Pastikan path yang direkonstruksi valid
            if (!path.empty() && path.front() == start_node_id) {
                 return path;
            } else {
                 return {};
            }
        }

        // Iterasi semua tetangga v dari u
        if (graph.count(u)) {
            for (int v : graph.at(u)) {
                // Asumsi bobot setiap edge adalah 1 (bergerak ke sel tetangga)
                int weight = 1;
                // Jika ditemukan jalur yang lebih pendek ke v melalui u
                if (distances.count(v) && distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    previous_nodes[v] = u;
                    pq.push({distances[v], v});
                }
            }
        }
    }

    return {}; 
}