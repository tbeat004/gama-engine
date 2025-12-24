cmake_minimum_required(VERSION 3.14)
project(GamaEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build all components
add_subdirectory(GamaCore)
add_subdirectory(Editor)
add_subdirectory(Runtime)

# Set Editor as the default startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor)
