cd "%~dp0"
clang++ -o out/main.exe .\src\main.cpp .\src\camera.cpp .\src\Film.cpp .\src\shape\sphere.cpp .\src\renderer.cpp .\src\scene.cpp

cd .\out
.\main.exe