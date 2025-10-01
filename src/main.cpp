#include <glad/glad.h>
#include "core/window/window.h"
#include "core/menu/menu.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

int main()
{
    Window window(1280, 720, "JuegoTest");

    // Menú centrado y proporcional, no se puede mover ni redimensionar
    Menu mainMenu("Menu Principal", 0.5f, 0.5f,
                  MenuBehavior::Centered | MenuBehavior::Proportional | MenuBehavior::NoMove | MenuBehavior::NoResize,
                  GLFW_KEY_M);

    // Menú centrado y proporcional, se puede mover
    Menu settingsMenu("Ajustes", 0.4f, 0.6f,
                      MenuBehavior::Centered | MenuBehavior::Proportional,
                      GLFW_KEY_N);

    // Menú libre: se puede mover, redimensionar, sin centrado ni proporcional
    Menu freeMenu("Menu Libre", 0.3f, 0.3f,
                  MenuBehavior::Default,
                  GLFW_KEY_B);

    // Menú libre: se puede mover, no se peude redimensionar, sin centrado ni proporcional
    Menu freeMenuNoResize("Menu Libre 2", 0.3f, 0.3f,
                          MenuBehavior::Default | MenuBehavior::NoResize,
                          GLFW_KEY_V);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.getHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!window.shouldClose())
    {
        window.pollEvents();

        if (glfwGetKey(window.getHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window.getHandle(), true);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Renderizar menús
        mainMenu.render(window);
        settingsMenu.render(window);
        freeMenu.render(window);
        freeMenuNoResize.render(window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.swapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
