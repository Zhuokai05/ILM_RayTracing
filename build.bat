@echo off
setlocal

cd "%~dp0"

@REM set compiler=clang++ 
set compiler=g++ 
%compiler% -o out/main.exe .\src\main.cpp .\src\camera.cpp .\src\Film.cpp .\src\shape\sphere.cpp .\src\renderer.cpp .\src\scene.cpp

cd .\out
.\main.exe