#include <iostream>
#include <conio.h>
#include "../include/clear_screen.h"
#include "../include/render_maze.h"
#include "../include/render_dijkstra_path.h"
#include "../include/player_pos.h"
#include "../include/dijkstra.h"
#include "../include/help_dijkstra.h"

void showHelpDijkstra(
    int player_row_pos, int player_col_pos,
    int maze_exit_row, int maze_exit_col,
    const std::vector<std::vector<bool>>& maze,
    const std::map<int, std::vector<int>>& maze_graph)
{
    int num_cols = maze[0].size();

    clearScreen();
    std::cout << "Sedang mencari jalur terpendek menggunakan Dijkstra...\n";

    int start_node_id = player_row_pos * num_cols + player_col_pos;
    int end_node_id = maze_exit_row * num_cols + maze_exit_col;

    std::vector<int> shortest_path = findShortestPathDijkstra(maze_graph, start_node_id, end_node_id);

    if (shortest_path.empty() && !(start_node_id == end_node_id))
    {
        std::cout << "Tidak ada jalur ditemukan dari posisi saat ini ke keluar.\n";
    }
    else if (!shortest_path.empty())
    {
        std::cout << "Jalur terpendek ditemukan dengan " << shortest_path.size() - 1 << " langkah.\n";
        showPlayerPos(player_row_pos, player_col_pos);
        renderDijkstraPath(player_row_pos, player_col_pos, maze, shortest_path, num_cols);
    }
    else
    {
        std::cout << "Anda sudah berada di posisi keluar.\n";
    }

    std::cout << "\nTekan tombol apa saja untuk kembali ke permainan...";
    getch();

    clearScreen();
    showPlayerPos(player_row_pos, player_col_pos);
    renderMaze(player_row_pos, player_col_pos, maze);
    std::cout << "\nButuh bantuan? Tekan H untuk meminta bantuan.\n";
}
