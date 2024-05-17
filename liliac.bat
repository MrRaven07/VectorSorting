:main
    call :compileMain
    call :link
    call :run
    call :delete
exit /b

:compileMain
	g++ -c ajutor.cpp -IP:\Aps\SFML\SFML-2.6.0\include 
exit /b

:link
	g++ -o ajutor.exe ajutor.o -LP:\Aps\SFML\SFML-2.6.0\lib -lsfml-graphics -lsfml-window -lsfml-system
exit /b

:run
    .\ajutor.exe

:delete
    del FunctionsClass.o
	del main.o
exit \b



@REM @echo off
@REM rem Set the name of your C++ source file (without extension)
@REM set SOURCE_FILE=example

@REM rem Set the name of your output executable file
@REM set EXECUTABLE_FILE=example

@REM rem Set the path to your C++ compiler (assuming g++)
@REM set COMPILER=g++

@REM rem Compile the C++ source file into an executable
@REM %COMPILER% -o %EXECUTABLE_FILE%.exe %SOURCE_FILE%.cpp

@REM rem Run the compiled executable
@REM %EXECUTABLE_FILE%.exe

@REM rem Pause to see any error messages before the window closes
@REM pause
