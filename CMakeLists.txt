cmake_minimum_required(VERSION 3.14)
project(GamaEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Dependencies
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Lua REQUIRED)

# Define source files
set(SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Window.cpp
    ${CMAKE_SOURCE_DIR}/src/Shader.cpp
    ${CMAKE_SOURCE_DIR}/src/Renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/Entity.cpp
    ${CMAKE_SOURCE_DIR}/src/LuaTest.cpp
)

# Create executable
add_executable(GamaEngine ${SOURCE_FILES})

# Include directories
target_include_directories(GamaEngine PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/external
    ${LUA_INCLUDE_DIR}
)

# Link Dependencies
target_link_libraries(GamaEngine PRIVATE glfw glad::glad ${LUA_LIBRARIES})

# Copy shaders to the same directory as the executable
add_custom_command(TARGET GamaEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/shaders
    $<TARGET_FILE_DIR:GamaEngine>/shaders)
