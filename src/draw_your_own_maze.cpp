#include <string>
#include <vector>
#include <algorithm>

#include "../include/empty_maze.h"
#include "../include/maze_storage_queue.h"

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_opengl3.h"

#include "../sdl2/include/SDL2/SDL.h"
#include "../sdl2/include/SDL2/SDL_opengl.h"

int main(int, char **)
{
    /* MAZE STORAGE QUEUE INITIALIZATION */
    createStorageQueue();

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Algomaze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool show = true;
    std::string message_result = "";

    while (show)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                show = false;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("##");

        /* MAZE DRAW REGION */
        const int max_rows = 100;
        const int max_cols = 100;

        static int row_size_input = 0;
        static int col_size_input = 0;

        static int last_row = row_size_input;
        static int last_col = col_size_input;

        // batesin input dari 1 sampe max baris/kolomnya
        ImGui::BeginChild("HeaderContainer", ImVec2(0, 120), true);
        ImGui::InputInt("Row Size", &row_size_input);
        ImGui::InputInt("Column Size", &col_size_input);
        row_size_input = std::clamp(row_size_input, 1, max_rows);
        col_size_input = std::clamp(col_size_input, 1, max_cols);

        // spacing
        ImGui::Spacing();
        ImGui::Dummy(ImVec2(0.0f, 1.0f));
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Dummy(ImVec2(0.0f, 1.0f));

        /* Visualisasi storage queue sisa berapa lagi */
        int storage_left = storageQueueSizeLeft();
        int used_storage = storage_size - storage_left;

        /* buat warna kotak2 visualisasi */
        /* VISUALISASI STORAGE YANG TERSISA */
        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.6f, 0.8f, 1.0f));        // normal
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.3f, 0.7f, 0.9f, 1.0f)); // hovered
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.1f, 0.5f, 0.7f, 1.0f));  // clicked
        ImGui::Text("Storage Queue Left: %d", storage_left);
        for (int i = 0; i < storage_left; i++)
        {
            std::string label = "##StorageQueueAvailable" + std::to_string(i);
            ImGui::Selectable(label.c_str(), true, 0, ImVec2(25, 25));
            ImGui::SameLine();
        }
        ImGui::PopStyleColor(3);
        /* VISUALISASI STORAGE YANG DIPAKE */
        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.181f, 1.0f, 0.544f, 1.0f));  // normal
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.350f, 1.0f, 0.637f, 1.0f)); // hovered
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.000f, 0.920f, 0.407f, 1.0f));  // clicked
        for (int i = 0; i < used_storage; i++)
        {
            std::string label = "##StorageQueueUsed" + std::to_string(i);
            ImGui::Selectable(label.c_str(), true, 0, ImVec2(25, 25));
            ImGui::SameLine();
        }
        ImGui::PopStyleColor(3);
        
        ImGui::EndChild();

        static std::vector<std::vector<bool>> maze(row_size_input, std::vector<bool>(col_size_input, false));

        /* Simpen maze ke storage queue */
        if (ImGui::Button("Save maze"))
        {
            message_result = insertToStorageQueue(maze);
            ImGui::OpenPopup("Message");
        }
        ImGui::SameLine();

        /* Lihat maze yang udah disimpen */
        if (ImGui::Button("View saved maze"))
        {
            ImGui::OpenPopup("Saved Maze");
        }

        // popup modal abis save maze ke storage queue
        if (ImGui::BeginPopupModal("Message", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text(message_result.c_str());
            if (ImGui::Button("OK"))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }

        // popup modal liat maze yang udah di save ke storage queue
        if (ImGui::BeginPopupModal("Saved Maze", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Test");
            if (ImGui::Button("OK"))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }

        // Resize maze if input changed
        if (row_size_input != last_row || col_size_input != last_col)
        {
            maze.resize(row_size_input);
            for (int i = 0; i < row_size_input; ++i)
            {
                maze[i].resize(col_size_input, false);
            }
            last_row = row_size_input;
            last_col = col_size_input;
        }

        ImGui::Text("Draw your own maze!");
        ImGui::Text("Size: %dx%d", row_size_input, col_size_input);

        float cellSize = 15.0f;

        for (int i = 0; i < row_size_input; i++)
        {
            for (int j = 0; j < col_size_input; j++)
            {
                ImGui::PushID(i * col_size_input + j);

                ImGui::PushStyleColor(ImGuiCol_Button, maze[i][j] ? ImVec4(0.2f, 0.2f, 0.2f, 1.0f) : ImVec4(1, 1, 1, 1));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));

                if (ImGui::Button(" ", ImVec2(cellSize, cellSize)))
                {
                    maze[i][j] = !maze[i][j];
                }

                ImGui::PopStyleColor(3);
                ImGui::PopID();

                if (j < col_size_input - 1)
                    ImGui::SameLine();
            }
        }

        /* TABLE */
        // ImGui::BeginChild("TableRegion", ImVec2(100,100), true);
        // const int col = 5;
        // const int row = 5;
        // bool checkboxes[col][col] = {};
        // if (ImGui::BeginTable("table1", col, ImGuiTableFlags_Borders))
        // {
        //     for (int i = 0; i < row; i++)
        //     {
        //         ImGui::TableNextRow();
        //         for (int j = 0; j < col; j++)
        //         {
        //             ImGui::TableSetColumnIndex(j);
        //             std::string label = "##checkbox_" + std::to_string(i) + "_" + std::to_string(j);
        //             ImGui::Checkbox(label.c_str(), &checkboxes[i][j]);
        //         }
        //     }
        //     ImGui::EndTable();
        // }
        // ImGui::EndChild();

        // if (ImGui::BeginTable("table3", 25))
        // {
        //     for (int item = 0; item < 25; item++)
        //     {
        //         ImGui::TableNextColumn();
        //         std::string label = "##checkbox" + std::to_string(item);
        //         ImGui::Checkbox(label.c_str(), &checkboxes[item]);
        //     }
        //     ImGui::EndTable();
        // }

        if (ImGui::Button("Close"))
            show = false;
        ImGui::End();

        ImGui::Render();
        glViewport(0, 0, 800, 600);
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}