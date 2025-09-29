#include <glad/glad.h>
#include "core/window.h"
#include <iostream>
#include <imgui.h>

int main()
{
    Window window(800, 600, "JuegoTest");

    int lastWidth = 0, lastHeight = 0;
    WindowMode lastMode = WindowMode::Windowed;
    WindowMode lastPrevMode = WindowMode::Windowed;

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    while (!window.shouldClose())
    {
        window.pollEvents();

        if (glfwGetKey(window.getHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window.getHandle(), true);

        if (glfwGetKey(window.getHandle(), GLFW_KEY_1) == GLFW_PRESS)
            window.setResolution(800, 600);
        if (glfwGetKey(window.getHandle(), GLFW_KEY_2) == GLFW_PRESS)
            window.setResolution(1280, 720);
        if (glfwGetKey(window.getHandle(), GLFW_KEY_3) == GLFW_PRESS)
            window.setResolution(1920, 1080);

        if (glfwGetKey(window.getHandle(), GLFW_KEY_F) == GLFW_PRESS)
            window.setWindowMode(WindowMode::Fullscreen);
        if (glfwGetKey(window.getHandle(), GLFW_KEY_W) == GLFW_PRESS)
            window.setWindowMode(WindowMode::Windowed);
        if (glfwGetKey(window.getHandle(), GLFW_KEY_B) == GLFW_PRESS)
            window.setWindowMode(WindowMode::Borderless);

        if (window.getWidth() != lastWidth || window.getHeight() != lastHeight || window.getMode() != lastMode || window.getPrevMode() != lastPrevMode)
        {
            lastWidth = window.getWidth();
            lastHeight = window.getHeight();
            lastMode = window.getMode();
            lastPrevMode = window.getPrevMode();
            std::cout << "Window size: " << lastWidth << "x" << lastHeight
                      << " | Mode: " << static_cast<int>(lastMode)
                      << " | PrevMode: " << static_cast<int>(lastPrevMode) << "\n";
        }

        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.swapBuffers();
    }

    return 0;
}
