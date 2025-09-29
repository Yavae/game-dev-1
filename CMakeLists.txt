cmake_minimum_required(VERSION 3.20)
project(JuegoTest LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(JuegoTest 
    src/main.cpp 
    src/Core/window.cpp
)

# Buscar librerías
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Enlazar librerías
target_link_libraries(JuegoTest PRIVATE glfw glad::glad glm::glm imgui::imgui)

target_include_directories(JuegoTest PRIVATE 
    ${imgui_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-mingw-dynamic/include/imgui/backends
)