#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_opengl3.h"

#include "../sdl2/include/SDL2/SDL.h"
#include "../sdl2/include/SDL2/SDL_opengl.h"

#include "../include/read_maze_from_db.h"
#include "../include/is_maze_db_empty.h"
#include "../include/maze.h"
#include "../include/select_maze.h"

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
        ImGui::Begin("Maze Selection");

        ImGui::Text("Choose Maze to Play");
        int maze_total = mazeCount("database/maze.txt");
        static int selected = -1;
        std::vector<std::vector<bool>> default_maze = initiateMaze();

        // LOOPING MAZE YANG DEFAULT
        ImGui::RadioButton("Default", &selected, -1);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1, 1)); // spacing antara sel maze
        for (int i = 0; i < default_maze.size(); i++)
        {
            for (int j = 0; j < default_maze[0].size(); j++)
            {
                ImGui::PushID(("default_maze_" + std::to_string(i) + "_" + std::to_string(j)).c_str()); // id tiap sel maze ke-i
                ImGui::BeginDisabled(true);
                ImGui::PushStyleColor(ImGuiCol_Button, default_maze[i][j] ? ImVec4(0.2f, 0.2f, 0.2f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                ImGui::Button(" ", ImVec2(10, 10));
                ImGui::PopStyleColor(1);
                ImGui::EndDisabled();
                ImGui::PopID();

                if (j != default_maze[0].size() - 1)
                {
                    ImGui::SameLine();
                }
            }
        }
        ImGui::PopStyleVar();
        ImGui::Spacing();
        ImGui::Dummy(ImVec2(0.0f, 2.0f));

        if (maze_total == 0)
        {
            ImGui::Text("Anda belum memiliki maze custom. Ayo gambar!");
        }

        for (int i = 0; i < maze_total; i++)
        {
            std::vector<std::vector<bool>> maze = readMazeFromDB("database/maze.txt", i);

            ImGui::BeginGroup();

            // radio button buat di pilih
            std::string radio_button_label = "Maze " + std::to_string(i + 1);
            ImGui::RadioButton(radio_button_label.c_str(), &selected, i);

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1, 1)); // spacing antara sel maze
            for (int maze_row = 0; maze_row < maze.size(); maze_row++)
            {
                for (int maze_col = 0; maze_col < maze[0].size(); maze_col++)
                {
                    ImGui::PushID(("maze_" + std::to_string(i) + "_cell_" + std::to_string(maze_row) + "_" + std::to_string(maze_col)).c_str()); // id tiap sel maze ke-i
                    ImGui::BeginDisabled(true);
                    ImGui::PushStyleColor(ImGuiCol_Button, maze[maze_row][maze_col] ? ImVec4(0.2f, 0.2f, 0.2f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    ImGui::Button(" ", ImVec2(10, 10));
                    ImGui::PopStyleColor(1);
                    ImGui::EndDisabled();
                    ImGui::PopID();

                    if (maze_col != maze[0].size() - 1)
                    {
                        ImGui::SameLine();
                    }
                }
            }
            ImGui::PopStyleVar();
            ImGui::EndGroup();

            // sameline kalau maze masih ada
            // kalau udah habis, break ke bawah
            if (i != (maze_total - 1))
            {
                ImGui::SameLine();
            }
        }

        if (ImGui::Button("Select"))
        {
            selectMaze("database/currentMaze.txt", selected);
            show = false;
        }
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
