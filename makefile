all: compileMain compileHeader dynamiclink run 

compileMain:
	g++ -c main.cpp -IP:\Aps\SFML\SFML-2.6.1\include

compileHeader:
	g++ -c FunctionsClass.cpp -IP:\Aps\SFML\SFML-2.6.1\include


dynamiclink:
	g++ -o main.exe main.o FunctionsClass.o -LP:\Aps\SFML\SFML-2.6.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lwinmm -lgdi32 -lsfml-main -mwindows -std=c++17
staticlink:
	g++ -o main.exe main.o FunctionsClass.o -LP:\Aps\SFML\SFML-2.6.1\lib -static -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lopenal -lsndfile -lwinmm -lgdi32 -lsfml-main -mwindows

run: 
	./main.exe

remove:
	rm FunctionsClass.o
	rm main.o