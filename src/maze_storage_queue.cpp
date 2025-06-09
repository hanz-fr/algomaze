#include <iostream>
#include <vector>
#include <string>
#include <array>
#include "../include/maze_storage_queue.h"

struct storage_queue
{
    int top;
    std::array<std::vector<std::vector<bool>>, storage_size> storage;
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

int storageQueueSizeLeft()
{
    return storage_size - q.top;
}

int getCurrentTopQueue()
{
    return q.top;
}

std::array<std::vector<std::vector<bool>>, storage_size> &displayStorageQueue()
{
    return q.storage;
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
    }
}

std::string deleteFromStorageQueue()
{
    std::string message = "";
    if (isStorageQueueEmpty())
    {
        message = "Can't delete old maze because storage queue is empty.";
        std::cout << message << "\n";
        return message;
    }
    else
    {
        std::vector<std::vector<bool>> pop_maze = q.storage[0]; // ambil data maze yang paling depan, alias yang paling lama

        int pop_maze_row = pop_maze.size();
        int pop_maze_col = pop_maze[0].size();

        message = "Maze with " + std::to_string(pop_maze_row) + "x" + std::to_string(pop_maze_col) + " size has been removed from storage queue.";
        std::cout << message << "\n";

        // keluarin maze yang didepan itu, ini cuman ngegeser id aja
        for (int i = 1; i < q.top; i++)
        {
            q.storage[i - 1] = q.storage[i];
        }
        q.storage[q.top - 1].clear(); // baris paling terakhir sekarang kosong

        q.top--;

        return message;
    }
}