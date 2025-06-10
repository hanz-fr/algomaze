#include "../include/maze_storage_queue.h"
#include "../include/widgets/view_maze_modal.h"
#include "../include/read_maze_from_db.h"

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_opengl3.h"

#include "../sdl2/include/SDL2/SDL.h"
#include "../sdl2/include/SDL2/SDL_opengl.h"

void viewMazeModal()
{
    /* Lihat maze yang udah disimpen */
    if (ImGui::Button("View saved maze"))
    {
        ImGui::OpenPopup("Saved Maze");
    }
    ImGui::SameLine();

    /* Popup yang isinya semua Maze yang udah kesimpen di storage queue */
    if (ImGui::BeginPopupModal("Saved Maze", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (isStorageQueueEmpty())
        {
            ImGui::Text("Storage queue is empty.");
        }
        else
        {
            int q_top = getCurrentTopQueue();
            std::array<std::vector<std::vector<bool>>, storage_size> &storage_queue = displayStorageQueue();
            for (int i = 0; i < q_top; i++)
            {
                if (!storage_queue[i].empty())
                {
                    std::string button_label = "Maze " + std::to_string(i + 1) + "\n" + "(" + std::to_string(storage_queue[i].size()) + "x" + std::to_string(storage_queue[i][0].size()) + ")";
                    std::string popup_label = "Maze " + std::to_string(i + 1) + "(" + std::to_string(storage_queue[i].size()) + "x" + std::to_string(storage_queue[i][0].size()) + ")";
                    
                    if (ImGui::Button(button_label.c_str(), ImVec2(50, 50)))
                    {
                        ImGui::OpenPopup(popup_label.c_str());
                    }

                    if (ImGui::BeginPopupModal(popup_label.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
                    {
                        std::vector<std::vector<bool>> maze = readMazeFromDB("database/maze.txt", i);

                        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1, 1)); // spacing antara sel maze
                        for (int maze_row = 0; maze_row < maze.size(); maze_row++)
                        {
                            for (int maze_col = 0; maze_col < maze[0].size(); maze_col++)
                            {
                                ImGui::PushID(("cell_" + std::to_string(maze_row) + "_" + std::to_string(maze_col)).c_str()); // id tiap sel maze
                                ImGui::BeginDisabled(true);
                                ImGui::PushStyleColor(ImGuiCol_Button, maze[maze_row][maze_col] ? ImVec4(0.2f, 0.2f, 0.2f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                                ImGui::Button(" ", ImVec2(10, 10));
                                ImGui::PopStyleColor(1);
                                ImGui::EndDisabled();
                                ImGui::PopID();
                                
                                if (maze_col != maze[0].size() - 1)
                                ImGui::SameLine();
                            }
                        }
                        ImGui::PopStyleVar();

                        if (ImGui::Button("Close"))
                            ImGui::CloseCurrentPopup();
                        ImGui::EndPopup();
                    }
                }
            }
        }
        if (ImGui::Button("OK"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
}