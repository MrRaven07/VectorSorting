all: compileMain compileHeader link run 

compileMain:
	g++ -c main.cpp -IP:\Aps\SFML\SFML-2.6.0\include

compileHeader:
	g++ -c FunctionsClass.cpp -IP:\Aps\SFML\SFML-2.6.0\include


link:
	g++ -o main.exe main.o FunctionsClass.o -LP:\Aps\SFML\SFML-2.6.0\lib -static -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run: 
	./main.exe

remove:
	rm FunctionsClass.o
	rm main.o