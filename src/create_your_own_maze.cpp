#include <string>

#include "../include/empty_maze.h"

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_opengl3.h"

#include "../sdl2/include/SDL2/SDL.h"
#include "../sdl2/include/SDL2/SDL_opengl.h"

int main(int, char **)
{
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
        const int rows = 25;
        const int cols = 25;

        static int row_size_input = 0;
        static int col_size_input = 0;
        ImGui::InputInt("Row Size", &row_size_input);
        ImGui::InputInt("Column Size", &col_size_input);
        ImGui::Button("Save Maze");
        
        ImGui::Text("Draw your own maze!");
        ImGui::Text("Size: %dx%d", row_size_input, col_size_input);
        
        static bool maze[rows][cols] = {false}; // true = wall
        float cellSize = 15.0f; // seberapa gede kotak2nya
        for (int i = 0; i < row_size_input; i++)
        {
            for (int j = 0; j < col_size_input; j++)
            {
                ImGui::PushID(i * col_size_input + j);

                // Set button color based on wall/path
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