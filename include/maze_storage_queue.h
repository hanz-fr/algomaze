#ifndef MAZE_STORAGE_QUEUE_H
#define MAZE_STORAGE_QUEUE_H
#include <vector>
#include <string>

void createStorageQueue();
void displayStorageQueue();
std::string insertToStorageQueue(std::vector<std::vector<bool>> maze_data);
void deleteFromStorageQueue();

#endif
