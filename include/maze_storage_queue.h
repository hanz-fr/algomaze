#ifndef MAZE_STORAGE_QUEUE_H
#define MAZE_STORAGE_QUEUE_H
#include <vector>
#include <string>

const int storage_size = 3;

bool isStorageQueueEmpty();
void createStorageQueue();
int storageQueueSizeLeft();
int getCurrentTopQueue();
std::array<std::vector<std::vector<bool>>, storage_size> &displayStorageQueue();
std::string insertToStorageQueue(std::vector<std::vector<bool>> maze_data);
std::string deleteFromStorageQueue();

#endif
