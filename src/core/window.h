#pragma once
#include <GLFW/glfw3.h>

enum class WindowMode
{
    Windowed,
    Fullscreen,
    Borderless
};

class Window
{
public:
    Window(int width, int height, const char *title, WindowMode mode = WindowMode::Windowed);
    ~Window();

    void setResolution(int width, int height);
    void setWindowMode(WindowMode mode);

    bool shouldClose() const;
    void pollEvents() const;
    void swapBuffers() const;
    GLFWwindow *getHandle() const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    WindowMode getMode() const { return mode; }
    WindowMode getPrevMode() const { return prevMode; }

private:
    void applyMode();
    GLFWwindow *handle;
    int width, height;
    int prevWidth, prevHeight;
    WindowMode mode;
    WindowMode prevMode;
};
