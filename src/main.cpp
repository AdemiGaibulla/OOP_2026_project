#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <chrono>
#include <exception>
#include <string>
#include <vector>

#include "Backend/Factory.h"
#include "Frontend/DashboardUI.h"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    // Window/rendering setup stays in main because it belongs to the app shell.
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_Window* window = SDL_CreateWindow(
        "Factory Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (window == nullptr) {
        SDL_Quit();
        return 1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    Factory factory;
    DashboardUI dashboard;
    std::string runtimeError;
    auto lastSimulationStep = std::chrono::steady_clock::now();

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        SimulationCmd simCmd;
        MachineCmd machineCmd;

        // UI receives copies only. It never touches live backend objects directly.
        std::vector<MachineSnap> machineSnaps = factory.getSnapshots();
        std::vector<ConveyorSnap> conveyorSnaps = factory.getConveyorSnapshots();
        FactoryStats stats = factory.getStats();
        dashboard.appendLogs(factory.takeEventLogs());

        dashboard.render(machineSnaps, conveyorSnaps, stats, simCmd, machineCmd);

        if (!runtimeError.empty()) {
            ImGui::Begin("Runtime Error");
            ImGui::TextWrapped("%s", runtimeError.c_str());
            ImGui::End();
        }

        try {
            // main.cpp is the only bridge that knows both UI commands and Factory.
            factory.applyCmd(simCmd);
            factory.applyMachineCmd(machineCmd);

            auto now = std::chrono::steady_clock::now();
            if (dashboard.consumeResetClockRequest()) {
                lastSimulationStep = now;
            }

            // At 1x, one simulation tick takes 0.7 seconds. Higher speeds divide that interval.
            const auto tickInterval = std::chrono::milliseconds(700 / dashboard.getSpeed());
            int catchUpTicks = 0;
            while (now - lastSimulationStep >= tickInterval && catchUpTicks < 10) {
                factory.update();
                lastSimulationStep += tickInterval;
                catchUpTicks++;
            }

            runtimeError.clear();
        }
        catch (const std::exception& e) {
            runtimeError = e.what();
        }

        ImGui::Render();

        int display_w = 0;
        int display_h = 0;
        SDL_GL_GetDrawableSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.08f, 0.08f, 0.09f, 1.0f);
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
