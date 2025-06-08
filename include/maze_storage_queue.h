#ifndef MAZE_STORAGE_QUEUE_H
#define MAZE_STORAGE_QUEUE_H
#include <vector>
#include <string>

const int storage_size = 3;

void createStorageQueue();
void displayStorageQueue();
int storageQueueSizeLeft();
std::string insertToStorageQueue(std::vector<std::vector<bool>> maze_data);
void deleteFromStorageQueue();

#endif
