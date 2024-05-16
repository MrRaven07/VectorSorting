#ifndef HEADERCLASS_H
#define HEADERCLASS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <windows.h> // for sleep



class game {
    private:
    int widthC;
    int heightC;
    sf::RenderWindow mwindow;


    sf::Clock clock;
    sf::Time timeSinceLastUpdate;
    const sf::Time TimePerFrame=sf::seconds(1.f / 60.f);


    int whichMode=0;
    /*
    whichMode:
    0 introduction
    1 menu (which sets the type of sorting)
    2 vector sorting
    3 help mode
    10 insertion sort
    */

    /*
    HELP MODE
    esc - exit
    h - help/settings
    x or m or s(top) (ill decide which) - main menu
    */


    sf::Font RobotoFont;
    
    sf::Text vectorSorting;
    float opacityVectorSorting = 0;

    sf::Text EscExit;
    sf::Text MMenu;

    sf::Text numeTipSortare;





    int sortariMeniu[30];
    sf::RectangleShape patrateMeniu;



    int limita; // echivalent cu n
    int vector[1001]; // echivalent cu v[]
    int culori[1001]; // puteam sa creez o structura care sa le cuprinda pe ambele
    sf::RectangleShape linie;
    




    void vectorInit();
    void WaitDisplayVector();

    void WaitingTime();


    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


    void processEvents();



    void changeColorsMode(int mode, int indice);

    void VectorOutputFunction();

    void SelectionSort();
    void BubbleSort();
    void InsertionSort();

    void MergeSort();
    void MergeSortRecursiv(int tmp[], int st, int dr);




    void renderer();

    void update();


    public:

    game(int width_, int height_);
    void run();

};

#endif