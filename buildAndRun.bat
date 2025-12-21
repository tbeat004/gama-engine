@echo off
cmake --preset debug
cmake --build --preset debug
cd build\debug
GamaEngine.exe
cd ..\..