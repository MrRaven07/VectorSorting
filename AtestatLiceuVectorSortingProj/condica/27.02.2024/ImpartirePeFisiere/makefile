# all: compile link run


# compile:
# 	g++ -c main.cpp -IP:\Aps\SFML\SFML-2.6.0\include -DSFML_STATIC

# link:
# 	g++ main.o -o main.exe -LP:\Aps\SFML\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system

# run: 
# 	./main.exe



all: compileMain compileHeader link run


compileMain:
	g++ -c main.cpp -IP:\Aps\SFML\SFML-2.6.0\include -DSFML_STATIC

compileHeader:
	g++ -c FunctionsClass.cpp -IP:\Aps\SFML\SFML-2.6.0\include -DSFML_STATIC


link:
	g++ -o main.exe main.o FunctionsClass.o -LP:\Aps\SFML\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system
	# g++ main.o FunctionsClass.o -o main.exe -LP:\Aps\SFML\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system

run: 
	./main.exe




# all: main clean

# main: 
# 	g++ -c main.cpp
#     g++ -c FunctionsClass.cpp
# 	g++ -o main.exe main.o FunctionsClass.o

# clean:
#     rm -rf *.o main



	

	