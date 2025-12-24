@echo off
cmake --preset debug
cmake --build --preset debug
cd build\debug\Editor
Editor.exe
cd ..\..\..
