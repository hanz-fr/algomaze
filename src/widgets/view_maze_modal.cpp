#include "../include/maze_storage_queue.h"
#include "../include/widgets/view_maze_modal.h"

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

    // popup modal liat maze yang udah di save ke storage queue
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
                    ImGui::Text("Maze %dx%d", storage_queue[i].size(), storage_queue[i][0].size());
                }
            }
        }
        if (ImGui::Button("OK"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
}