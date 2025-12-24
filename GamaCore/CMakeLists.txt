cmake_minimum_required(VERSION 3.14)

# EngineCore Static Library
project(EngineCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Dependencies
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Lua REQUIRED)

# Source files
set(CORE_SOURCES
    src/Window.cpp
    src/Shader.cpp
    src/Renderer.cpp
    src/Entity.cpp
    src/Scripting/LuaEngine.cpp
)

# Create static library
add_library(EngineCore STATIC ${CORE_SOURCES} "src/Scene.cpp")

# Public include directories (accessible to Editor/Runtime)
target_include_directories(EngineCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external
    ${LUA_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(EngineCore PUBLIC
    glfw
    glad::glad
    ${LUA_LIBRARIES}
)

# Copy shaders to build directory
add_custom_command(TARGET EngineCore POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders
    ${CMAKE_BINARY_DIR}/shaders
)
