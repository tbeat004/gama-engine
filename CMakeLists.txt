cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(GamaEngine)



# Find Dependencies
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# Define source files
set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Create executable
add_executable(GamaEngine ${SOURCE_FILES})

# Link Dependencies
target_link_libraries(GamaEngine PRIVATE glfw glad::glad)
