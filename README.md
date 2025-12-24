# gama-engine
A small C++ game engine project with embedded Lua scripting.

## Prerequisites

You need these installed on your system:
- Visual Studio 2026 with C++ workload
- vcpkg (with `VCPKG_ROOT` environment variable set)
- CMake 3.20+
- Ninja

## Build and Run

```bash
buildAndRun.bat
```

That's it! Dependencies are automatically installed via vcpkg manifest on first build.

## Dependencies

All dependencies are automatically managed via vcpkg.json:
- **Lua 5.4.8** - Scripting
- **GLFW3** - Window and input
- **GLEW** - OpenGL extensions
- **Sol2** - C++ Lua bindings (included in external/)
