all: compileMain compileHeader link run remove

compileMain:
	g++ -c main.cpp -IP:\Aps\SFML\SFML-2.6.0\include 
	# g++ -c main.cpp -IP:\Aps\SFML\SFML-2.6.0\include -DSFML_STATIC -static -static-libgcc -static-libstdc++

compileHeader:
	g++ -c FunctionsClass.cpp -IP:\Aps\SFML\SFML-2.6.0\include  
	# g++ -c FunctionsClass.cpp -IP:\Aps\SFML\SFML-2.6.0\include -DSFML_STATIC -static -static-libgcc -static-libstdc++


link:
	g++ -o main.exe main.o FunctionsClass.o -LP:\Aps\SFML\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system
	# g++ main.o FunctionsClass.o -o main.exe -LP:\Aps\SFML\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system

run: 
	./main.exe

remove:
	rm FunctionsClass.o
	rm main.o

	

	