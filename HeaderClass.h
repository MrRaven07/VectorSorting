#ifndef HEADERCLASS_H
#define HEADERCLASS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include <map>
#include <list>


class game {
    private:

    bool isFull;
    sf::View view;

    int screenWidth;
    int screenHeight;
    int widthC;
    int heightC;
    sf::RenderWindow mwindow;


    sf::Clock clock;
    sf::Time TimePerFrame;



    char CeSortare[101][101]=
    {
        "EROAAAAAAAAAAAAAAAAAAAAAARE",
        "Selection Sort",
        "Bubble Sort",
        "Insertion Sort",
        "Binary Insertion Sort",
        "Merge Sort"
    };
    sf::Text CeSortareText;
    
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
    sf::Text numeTipSortare; // ???????
    int numarSortari;
    void MouseCheckMeniu(int mouseX, int mouseY, bool click);
    sf::RectangleShape patrateMeniu;
    sf::Vector2f patrateMeniuDimensiune;
    sf::Vector2i patrateMeniuVector[10];
    int PatrateTextState=0;
    sf::Text PatrateTextSFML;
    wchar_t PatrateText[10][500] = {
        L"",
        L"Selection Sort - Algoritmul selectează în mod repetat cel mai mic (sau cel mai mare) element \ndin porțiunea nesortată a listei și îl schimbă cu primul element al părții nesortate. Acest proces \nse repetă pentru porțiunea rămasă nesortată până când întreaga listă este sortată.",
        L"Bubble Sort - Bubble Sort este cel mai simplu algoritm de sortare care funcționează prin schimbarea în mod \nrepetat a elementelor adiacente dacă acestea sunt în ordinea greșită. Acest algoritm nu \neste potrivit pentru seturi mari de date, deoarece complexitatea sa medie și în \ncel mai rău caz este destul de mare.",
        L"Insertion Sort - Sortarea prin inserare este un algoritm simplu de sortare care funcționează prin inserarea \niterativă a fiecărui element dintr-o listă nesortată în poziția sa corectă într-o \nporțiune sortată a listei. Este un algoritm de sortare stabil, ceea ce înseamnă că \nelementele cu valori egale își mențin ordinea relativă în rezultatul sortat.",
        L"Binary Insertion Sort - Sortarea prin inserție binară este un algoritm de sortare care este similar cu sortarea \nprin inserție, dar în loc să folosim căutarea liniară pentru a găsi locația în \ncare ar trebui să fie inserat un element, folosim căutarea binară. Astfel, reducem \nvaloarea comparativă a inserării unui singur element de la O(N) la O(log N).",
        L"Merge Sort - Sortarea prin îmbinare este un algoritm de sortare care urmează abordarea împărțiți și cuceriți. \nFuncționează prin împărțirea recursivă a matricei de intrare în subregii mai mici \nși sortarea acelor subgrupuri, apoi îmbinându-le înapoi împreună pentru a obține \nmatricea sortată."
    };
    sf::Text FPSText;
    int limita; // echivalent cu n
    int vector[1001]; // echivalent cu v[]
    int culori[1001]; // puteam sa creez o structura care sa le cuprinda pe ambele
    std::map<int,int> culoriM;
    std::list<unsigned short int> culoriVechi;
    sf::RectangleShape linie;
    double latimeLinie;
    double inaltimeFraction;
    void vectorInit();
    void WaitDisplayVector(int modeRightNow);
    void WaitingTime(float adjustTime = 1.f);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void processEvents();
    void changeColorsMode(int mode, int indice);
    void VectorOutputFunction();
    void SelectionSort();
    void BubbleSort();
    void InsertionSort();
    void BinaryInsertionSort();
    void MergeSort();
    void MergeSortRecursiv(int tmp[], int st, int dr);
    void ToggleFullscreen();
    void renderer();
    void update();

    public:
    game(int width_, int height_);
    void run();

};

#endif