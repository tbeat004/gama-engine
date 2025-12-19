@echo off
cmake --build build --config Debug
cd build\Debug
GamaEngine.exe
cd ..\..