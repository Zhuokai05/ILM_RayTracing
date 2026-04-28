@echo off
setlocal

cd "%~dp0"

set compiler=clang++ 
@REM set compiler=g++
@REM set compiler=cl 

mkdir out
%compiler% ^
    -g ^
    -std=c++17 ^
    -o out/main.exe ^
        .\src\main.cpp .\src\camera.cpp .\src\Film.cpp .\src\renderer.cpp .\src\scene.cpp ^
        .\src\shape\sphere.cpp .\src\shape\quad.cpp ^
        .\src\light\light_directional.cpp .\src\light\light_ambient.cpp .\src\light\light_point.cpp ^
    -isystem vendor

cd .\out
.\main.exe