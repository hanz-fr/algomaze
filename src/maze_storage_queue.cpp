#include <iostream>
#include <vector>
#include <string>
#include "../include/maze_storage_queue.h"

struct storage_queue
{
    int top;
    std::vector<std::vector<bool>> storage[storage_size];
} q;

void createStorageQueue()
{
    q.top = 0;
}

bool isStorageQueueEmpty()
{
    return q.storage[0].size() == 0;
}

bool isStorageQueueFull()
{
    return q.top >= storage_size;
}

void displayStorageQueue()
{
    if (isStorageQueueEmpty())
    {
        std::cout << "Storage queue is empty." << "\n";
    }
    else
    {
        std::cout << "Displaying list of maze (rows and cols size) inside storage queue: " << "\n";
        for (int i = 0; i < storage_size; i++)
        {
            std::cout << q.storage[i].size() << "x" << q.storage[i][0].size() << "\n";
        }
    }
}

int storageQueueSizeLeft()
{
    return storage_size - q.top;
}

std::string insertToStorageQueue(std::vector<std::vector<bool>> maze_data)
{
    std::string message = "";
    int maze_data_row = maze_data.size();
    int maze_data_col = maze_data[0].size();

    if (isStorageQueueFull())
    {
        message = "Can't add more maze because storage queue is full.\nConsider subscribing to get more storage.";
        std::cout << message << "\n";
        return message;
    }
    else
    {
        q.storage[q.top] = maze_data; // masukkin maze yg baru ke dalem queue

        // PESAN BERHASIL
        std::string message = "Maze with " + std::to_string(maze_data_row) + "x" + std::to_string(maze_data_col) + " size has been added to storage queue.";
        std::cout << message << "\n";
        q.top++;
        return message;

        // tambah q nya 1
        q.top++;
        return message;
    }
}

void deleteFromStorageQueue()
{
    if (isStorageQueueEmpty())
    {
        std::cout << "Can't delete because queue is empty." << "\n";
    }
    else
    {
        std::vector<std::vector<bool>> pop_maze = q.storage[0]; // keluarin maze yang didepan antrian

        int pop_maze_row = pop_maze.size();
        int pop_maze_col = pop_maze[0].size();

        std::cout << "Maze with " << pop_maze_row << "x" << pop_maze_col << " size has been removed from storage queue." << "\n";
        for (int i = 0; i < storage_size; i++)
        {
            q.storage[i - 1] = q.storage[i];
        }
        q.storage[storage_size - 1] = {};
    }
}