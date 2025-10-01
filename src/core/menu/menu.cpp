#include "menu.h"
#include <GLFW/glfw3.h>
#include <imgui.h>

void Menu::render(Window &window)
{
    // Abrir menú con tecla si está cerrado
    if (!showMenu && glfwGetKey(window.getHandle(), toggleKey) == GLFW_PRESS)
        showMenu = true;

    if (!showMenu)
        return;

    ImGuiIO &io = ImGui::GetIO();

    // Tamaño proporcional
    ImVec2 size(600, 400);
    if (hasBehavior(behavior, MenuBehavior::Proportional))
        size = ImVec2(io.DisplaySize.x * widthRatio, io.DisplaySize.y * heightRatio);

    // Posición centrada
    if (hasBehavior(behavior, MenuBehavior::Centered))
    {
        ImVec2 center(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
        ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    }

    // Flags de ventana
    ImGuiWindowFlags flags = 0;
    if (hasBehavior(behavior, MenuBehavior::NoMove))
        flags |= ImGuiWindowFlags_NoMove;
    if (hasBehavior(behavior, MenuBehavior::NoResize))
        flags |= ImGuiWindowFlags_NoResize;
    if (!hasBehavior(behavior, MenuBehavior::FixedSize) && !hasBehavior(behavior, MenuBehavior::Proportional))
        ImGui::SetNextWindowSize(size, ImGuiCond_Always);

    // Mostrar ventana, cerrar con la X
    ImGui::Begin(title, &showMenu, flags);

    ImGui::Text("Resoluciones:");
    if (ImGui::Button("800x600"))
        window.setResolution(800, 600);
    if (ImGui::Button("1280x720"))
        window.setResolution(1280, 720);
    if (ImGui::Button("1920x1080"))
        window.setResolution(1920, 1080);

    ImGui::Separator();

    ImGui::Text("Modo de ventana:");
    if (ImGui::Button("Ventana"))
        window.setWindowMode(WindowMode::Windowed);
    if (ImGui::Button("Pantalla completa"))
        window.setWindowMode(WindowMode::Fullscreen);
    if (ImGui::Button("Sin bordes"))
        window.setWindowMode(WindowMode::Borderless);

    ImGui::End();
}
