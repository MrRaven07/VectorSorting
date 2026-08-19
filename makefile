# Configuration Variables
CXX = "compilerAndLibraries\winlibs-i686-posix-dwarf-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5\mingw32\bin\g++.exe"

INCLUDE_FLAGS = -I"compilerAndLibraries\SFML-2.6.2\include"
LIB_FLAGS = -L"compilerAndLibraries\SFML-2.6.2\lib"

DYNAMIC_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lwinmm -lgdi32 -lsfml-main -mwindows -std=c++17
STATIC_FLAGS = -static -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lfreetype -lopengl32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lwinmm -lgdi32 -lsfml-main -mwindows -static-libgcc -static-libstdc++ -std=c++17


# Command Routing
# Default target for a simple "make"
all: dynamiclink run

# TARGET: dynamiclink 
dynamiclink: compileMain compileHeader
	$(CXX) -o bin/main.exe main.o FunctionsClass.o $(LIB_FLAGS) $(DYNAMIC_FLAGS)

compileMain:
	$(CXX) -c src/main.cpp $(INCLUDE_FLAGS)

compileHeader:
	$(CXX) -c src/FunctionsClass.cpp $(INCLUDE_FLAGS)

# TARGET: staticlink 
staticlink: compileMainStatic compileHeaderStatic
	$(CXX) -o release/main.exe main.o FunctionsClass.o $(LIB_FLAGS) $(STATIC_FLAGS)

compileMainStatic:
	$(CXX) -c src/main.cpp $(INCLUDE_FLAGS) -DSFML_STATIC

compileHeaderStatic:
	$(CXX) -c src/FunctionsClass.cpp $(INCLUDE_FLAGS) -DSFML_STATIC

# TARGET: run
run: 
	bin\main.exe

# TARGET: remove

remove:
	del main.o
	del FunctionsClass.o