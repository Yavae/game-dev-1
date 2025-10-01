#pragma once
#include "../window/window.h"
#include <imgui.h>

enum class MenuBehavior
{
    Default = 0,
    Centered = 1 << 0,
    Proportional = 1 << 1,
    FixedSize = 1 << 2,
    NoMove = 1 << 3,
    NoResize = 1 << 4
};

inline MenuBehavior operator|(MenuBehavior a, MenuBehavior b)
{
    return static_cast<MenuBehavior>(static_cast<int>(a) | static_cast<int>(b));
}

inline bool hasBehavior(MenuBehavior value, MenuBehavior flag)
{
    return (static_cast<int>(value) & static_cast<int>(flag)) != 0;
}

class Menu
{
public:
    Menu(const char *title,
         float widthRatio = 0.5f,
         float heightRatio = 0.5f,
         MenuBehavior behavior = MenuBehavior::Centered | MenuBehavior::Proportional | MenuBehavior::NoMove | MenuBehavior::NoResize,
         int toggleKey = GLFW_KEY_M)
        : title(title), widthRatio(widthRatio), heightRatio(heightRatio),
          behavior(behavior), toggleKey(toggleKey) {}

    void render(Window &window);

    void toggle() { showMenu = !showMenu; }
    void open() { showMenu = true; }
    void close() { showMenu = false; }

    void setBehavior(MenuBehavior b) { behavior = b; }
    void setSizeRatio(float w, float h)
    {
        widthRatio = w;
        heightRatio = h;
    }

    int getToggleKey() const { return toggleKey; }

private:
    const char *title;
    bool showMenu = false;
    float widthRatio;
    float heightRatio;
    MenuBehavior behavior;
    int toggleKey;
};
