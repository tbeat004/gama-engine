cmake_minimum_required(VERSION 3.14)

# Runtime Executable
project(Runtime)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(RUNTIME_SOURCES
    src/main.cpp
)

# Create executable
add_executable(Runtime ${RUNTIME_SOURCES})

# Link EngineCore
target_link_libraries(Runtime PRIVATE EngineCore)
