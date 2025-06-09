#include "../include/maze_storage_queue.h"
#include "../include/widgets/delete_old_maze_modal.h"

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_opengl3.h"

#include "../sdl2/include/SDL2/SDL.h"
#include "../sdl2/include/SDL2/SDL_opengl.h"

void deleteOldMazeModal(std::string& message_result)
{
    /* Simpen maze ke storage queue */
    if (ImGui::Button("Delete Oldest Maze"))
    {
        message_result = deleteFromStorageQueue();
        ImGui::OpenPopup("DeleteMessage");
    }

    // popup modal abis save maze ke storage queue
    if (ImGui::BeginPopupModal("DeleteMessage", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text(message_result.c_str());
        if (ImGui::Button("OK"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
}