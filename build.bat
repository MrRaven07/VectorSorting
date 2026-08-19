@echo off

:: Usage:
:: build staticlink
:: build dynamiclink
:: build remove

:: build 
:: Automatically builds it as dynamiclink

@echo off


:: Compiler executable (Compiler path)
set CXX="compilerAndLibraries\winlibs-i686-posix-dwarf-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5\mingw32\bin\g++.exe"

:: Include and Library paths
set INCLUDE_FLAGS=-I"compilerAndLibraries\SFML-2.6.2\include"
set LIB_FLAGS=-L"compilerAndLibraries\SFML-2.6.2\lib"

:: Linker flags
set DYNAMIC_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lwinmm -lgdi32 -lsfml-main -mwindows -std=c++17
set STATIC_FLAGS=-static -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lfreetype -lopengl32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lwinmm -lgdi32 -lsfml-main -mwindows -static-libgcc -static-libstdc++ -std=c++17


:: Command Routing, Flags given to the executable
if "%1"=="staticlink" goto staticlink
if "%1"=="dynamiclink" goto dynamiclink
if "%1"=="remove" goto remove
if "%1"=="run" goto run

:: Default behavior: If no argument is provided, fall through to dynamic
goto dynamiclink


:: TARGET: dynamiclink (Default)
:dynamiclink
echo [1/4] Compiling main.cpp
%CXX% -c src/main.cpp %INCLUDE_FLAGS%

echo [2/4] Compiling FunctionsClass.cpp
%CXX% -c src/FunctionsClass.cpp %INCLUDE_FLAGS%

echo [3/4] Linking dynamically
%CXX% -o bin/main.exe main.o FunctionsClass.o %LIB_FLAGS% %DYNAMIC_FLAGS%

echo [4/4] Running application
"bin/main.exe"

goto end



:: TARGET: staticlink
:staticlink
echo [1/3] Compiling main.cpp
%CXX% -c src/main.cpp %INCLUDE_FLAGS% -DSFML_STATIC

echo [2/3] Compiling FunctionsClass.cpp
%CXX% -c src/FunctionsClass.cpp %INCLUDE_FLAGS% -DSFML_STATIC

echo [3/3] Linking statically
%CXX% -o "release/main.exe" main.o FunctionsClass.o %LIB_FLAGS% %STATIC_FLAGS%

goto end

:: TARGET: run
:run
"bin/main.exe"

goto end

:: TARGET: remove
:remove
echo Deleting object files
del FunctionsClass.o
del main.o

:end