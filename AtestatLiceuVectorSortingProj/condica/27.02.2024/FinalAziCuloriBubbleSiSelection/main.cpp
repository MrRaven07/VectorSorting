#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <windows.h> // for sleep

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

    // sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    

    return 0;
}