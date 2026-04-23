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
    .\src\main.cpp .\src\camera.cpp .\src\Film.cpp .\src\shape\sphere.cpp .\src\renderer.cpp .\src\scene.cpp .\src\light\light_directional.cpp ^
    -isystem vendor

cd .\out
.\main.exe