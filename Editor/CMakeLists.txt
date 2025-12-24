cmake_minimum_required(VERSION 3.14)

# Editor Executable
project(Editor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find ImGui
find_package(imgui CONFIG REQUIRED)

# Source files
set(EDITOR_SOURCES
    src/main.cpp
    src/EditorApp.cpp
)

# Create executable
add_executable(Editor ${EDITOR_SOURCES})

# Include directories
target_include_directories(Editor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link EngineCore and ImGui
target_link_libraries(Editor PRIVATE
    EngineCore
    imgui::imgui
)

# Set as startup project in Visual Studio
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor)
