all: compileMain compileHeader link run 

compileMain:
	g++ -c main.cpp -IP:\Aps\SFML\SFML-2.6.0\include 

compileHeader:
	g++ -c FunctionsClass.cpp -IP:\Aps\SFML\SFML-2.6.0\include  


link:
	g++ -o main.exe main.o FunctionsClass.o -LP:\Aps\SFML\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system

run: 
	./main.exe

remove:
	rm FunctionsClass.o
	rm main.o

nothing:
	compileMain
	# g++ -c main.cpp -IP:\Aps\SFML\SFML-2.6.0\include -DSFML_STATIC -static -static-libgcc -static-libstdc++


	compile header
	# g++ -c FunctionsClass.cpp -IP:\Aps\SFML\SFML-2.6.0\include -DSFML_STATIC -static -static-libgcc -static-libstdc++

	# g++ main.o FunctionsClass.o -o main.exe -LP:\Aps\SFML\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system


	