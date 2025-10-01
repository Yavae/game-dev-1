#include <glad/glad.h>
#include "window.h"
#include <stdexcept>
#include <iostream>

Window::Window(int width, int height, const char *title, WindowMode mode)
{

    if (!glfwInit())
        throw std::runtime_error("GLFW init failed");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->width = width;
    this->height = height;
    this->mode = mode;

    GLFWmonitor *monitor = (mode == WindowMode::Windowed) ? nullptr : glfwGetPrimaryMonitor();

    handle = glfwCreateWindow(width, height, title, monitor, nullptr);
    if (!handle)
        throw std::runtime_error("Window creation failed");

    glfwMakeContextCurrent(handle);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("GLAD init failed");

    glEnable(GL_DEPTH_TEST);

    if (mode != WindowMode::Windowed)
        applyMode();
}

Window::~Window()
{
    glfwDestroyWindow(handle);
    glfwTerminate();
}

bool Window::shouldClose() const { return glfwWindowShouldClose(handle); }
void Window::pollEvents() const { glfwPollEvents(); }
void Window::swapBuffers() const { glfwSwapBuffers(handle); }
GLFWwindow *Window::getHandle() const { return handle; }

void Window::setResolution(int w, int h)
{
    if (mode != WindowMode::Windowed)
        return;

    if (width == w && height == h)
        return;

    prevHeight = height;
    prevWidth = width;
    width = w;
    height = h;
    applyMode();
}

void Window::setWindowMode(WindowMode m)
{
    if (mode == m)
        return;
    prevMode = mode;
    mode = m;
    applyMode();
}

void Window::applyMode()
{
    GLFWmonitor *monitor = glfwGetWindowMonitor(handle);

    int xpos, ypos;
    glfwGetWindowPos(handle, &xpos, &ypos);

    std::cout << "Window size: " << xpos << "x" << ypos << "\n";

    if (mode == WindowMode::Windowed)
    {
        if (xpos <= 0 || ypos <= 0)
        {
            xpos = 0;
            ypos = 30;
        }

        glfwSetWindowAttrib(handle, GLFW_DECORATED, GLFW_TRUE);
        glfwSetWindowAttrib(handle, GLFW_RESIZABLE, GLFW_TRUE);

        glfwSetWindowMonitor(handle, nullptr, xpos, ypos, width, height, GLFW_DONT_CARE);
    }
    else if (mode == WindowMode::Fullscreen)
    {
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *vm = glfwGetVideoMode(monitor);
        width = vm->width;
        height = vm->height;

        glfwSetWindowAttrib(handle, GLFW_DECORATED, GLFW_FALSE);
        glfwSetWindowAttrib(handle, GLFW_RESIZABLE, GLFW_FALSE);

        glfwSetWindowMonitor(handle, monitor, xpos, ypos, width, height, vm->refreshRate);
    }
    else if (mode == WindowMode::Borderless)
    {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *vm = glfwGetVideoMode(monitor);
        width = vm->width;
        height = vm->height;

        glfwSetWindowAttrib(handle, GLFW_DECORATED, GLFW_FALSE);
        glfwSetWindowAttrib(handle, GLFW_RESIZABLE, GLFW_FALSE);

        glfwSetWindowMonitor(handle, nullptr, 0, 0, width, (height + 30), GLFW_DONT_CARE);
    }
}
