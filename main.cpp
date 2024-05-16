#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#include "HeaderClass.h"

int main()
{
    // int wid= sf::VideoMode::getDesktopMode().width;
    // int hei= sf::VideoMode::getDesktopMode().height;

    int widthS = 1280;
    int heightS = 720;
    srand(time(NULL));

    game Game(widthS, heightS);
    
    Game.run();


    return 0;
}


