@echo off
setlocal

cd "%~dp0"

@REM set compiler=clang++ 
set compiler=g++
@REM set compiler=cl 

mkdir out
%compiler% ^
    -g ^
    -o out/main.exe ^
    .\src\main.cpp .\src\camera.cpp .\src\Film.cpp .\src\shape\sphere.cpp .\src\renderer.cpp .\src\scene.cpp .\src\light\light_directional.cpp ^
    -Ivendor

cd .\out
.\main.exe