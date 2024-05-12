#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <windows.h> // for sleep


class game{
    private:
    int widthC;
    int heightC;
    sf::RenderWindow mwindow;

    int whichMode=0;
    /*
    whichMode:
    0 introduction
    1 menu (which sets the type of sorting)
    2 vector sorting
    3 help mode


    10 insertion sort


    99 KILL PROGRAM
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
    
    int unu; // insertion sort
    int doi;





    void vectorInit(){

        // Asocierea lui v[i] cu valoarea i
        for(int i=1;i<=limita;i++){
            vector[i]=i;
            culori[i]=1;
        }
        
        // Verificarea init-ului
        // for(int i=1;i<=limita;i++)
        //     std::cerr << vector[i] << ' ';
        // std::cout << '\n';

        // Randomizarea
        for(int i=1;i<=limita;i++){
            std::swap(vector[i], vector[rand()%limita+1]);
        }


        // Verificarea randomizarii
        // for(int i=1;i<=limita;i++)
        //     std::cerr << vector[i] << ' ';
        // std::cout << '\n';

        return;
    }





    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
        if (key == sf::Keyboard::Escape){
            whichMode = 99;
            // exit = 1;
        }
        if (key == sf::Keyboard::M){
            whichMode = 1;
        }    

        if (key == sf::Keyboard::F){
            whichMode = 10;
        }


        return;
    }



    void processEvents(){
        sf::Event event;
        while (mwindow.pollEvent(event)) {
            switch (event.type){
                case sf::Event::Closed:
                    mwindow.close();
                    break;
                
                case sf::Event::LostFocus:
                    //pause
                    break;
                case sf::Event::GainedFocus:
                    //resume
                    break;

                case sf::Event::KeyPressed:
                    handlePlayerInput(event.key.code, true);
                    break;

                case sf::Event::KeyReleased:
                    handlePlayerInput(event.key.code, false);
                    break;
            
            }
        }
    }   


    void changeColorsMode(int mode, int indice){
        // mode:
        // 1 - alb (nefolosit)
        // 2 - verde (in comparatie)
        // 3 - rosu (comparatie nereusita)
        // 4 - albastru (schimbare)

        // indice: reprezinta indicele din vector care trebuie schimbat

        culori[indice]=mode;

        return;
    }

    void insertionSort(){
        int inaltimeLinie;
                for(int i=1;i<=limita;i++){           
                    inaltimeLinie = vector[i]*5;
                    linie.setSize(sf::Vector2f(1,inaltimeLinie));
                    
                    
                    linie.setPosition(widthC/100 + i * 10, heightC-heightC/10-inaltimeLinie); 
                    switch(culori[i]){
                        case 1:
                        linie.setFillColor(sf::Color(255,255,255));
                        break;

                        case 2:
                        linie.setFillColor(sf::Color(0, 255, 0));
                        break;

                        case 3:
                        linie.setFillColor(sf::Color(255, 0, 0));
                        break;

                        case 4:
                        linie.setFillColor(sf::Color(0, 0, 255));
                        break;

                    }



                    // aparent cand se afiseaza, se afiseaza din dreapta sus
                    // de aceea trebuie sa ne asiguram de la inaltime afisam
                    // de la inaltimea maxima - inaltimeLinie ( inaltimeLinie fiind inaltimea fiecarei linii)
                    
                    mwindow.draw(linie);
                }

                // std::cerr << unu << ' ' << doi << '\n';
                // if(unu<limita){
                //     if(doi<=limita){ 
                //         if(vector[unu]>vector[doi]){
                //             std::swap(vector[unu],vector[doi]);
                //         }
                //     doi++;
                //     }
                //     else {
                //         unu=unu+1;
                //         doi=unu+1;
                //     }
                // }

                for(;unu<limita;){

                    if(doi>limita){
                        changeColorsMode(1, unu); // Colorarea indicelui inapoi in alb
                        unu++;
                        changeColorsMode(2, unu); // Colorarea indicelui in verde (urmeaza sa fie sortat) 
                        doi=unu+1;
                        }

                    for(;doi<=limita;){
                        changeColorsMode(2, doi); // Colorarea indicelui in verde (urmeaza sa fie comparat) 
                        if(vector[unu]>vector[doi]){
                            std::swap(vector[unu],vector[doi]);
                            changeColorsMode(4, doi);
                        }
                        else
                            changeColorsMode(3, doi);

                        
                        doi++;
                        goto exitINSERTION;
                    }
                }
                exitINSERTION:
        return;
    }


    void renderer(){
        return;
    }


    void update(){
        while(mwindow.isOpen()){
        
        // verifying events
        processEvents();
        mwindow.clear();



        switch(whichMode){
            case 0:
                if(opacityVectorSorting<255){
                    opacityVectorSorting+=1.f;
                    // opacityVectorSorting+=0.025f;
                }
                
                else {
                    // pregatire pentru MenuMode
                    whichMode=1;
                    vectorSorting.setCharacterSize(24);
                    vectorSorting.setPosition(vectorSorting.getPosition().x, vectorSorting.getPosition().y-heightC/4);
                    vectorSorting.setPosition(widthC/2 - (vectorSorting.getLocalBounds().width)/2, 0);
                    EscExit.setPosition(widthC-EscExit.getLocalBounds().width, 0);
                    MMenu.setPosition(0, 0);
                }
                vectorSorting.setColor(sf::Color(255,255,255,int(opacityVectorSorting)));
                mwindow.draw(vectorSorting);
            break;
            case 1: // menu
                mwindow.draw(vectorSorting);
                mwindow.draw(MMenu);
                mwindow.draw(EscExit);

                patrateMeniu.setPosition(widthC/4, heightC/2);

                for(int i=1;i<=10;i++){
                    patrateMeniu.setPosition(widthC/4 + i * 70, heightC/2);
                    mwindow.draw(patrateMeniu);
                }
            break;
            case 2:

            break;
            case 10:

                void insertionSort();
                
            break;
            case 99:

            return;
            
        }

        mwindow.display();


        
    }
    }

    // public    
    public:
    
    game(int width_, int height_) : mwindow(sf::VideoMode(width_, height_), "VectorSorting", sf::Style::None ) {
        widthC = width_;
        heightC = height_;
    

        limita = 100;
        vectorInit(); // initializeaza vectorul "vector", impreuna cu vectorul "culori"
        unu = 1;
        doi = 2;



        if (!RobotoFont.loadFromFile("Fonts/Roboto-Regular.ttf"))
            std::cerr << "Nu merge fisierul";


            
        
        vectorSorting.setFont(RobotoFont);
        vectorSorting.setString("Tipuri de sortari");
        vectorSorting.setCharacterSize(50);
        vectorSorting.setFillColor(sf::Color(255, 255, 255, 0));
        vectorSorting.setPosition(widthC/2 - (vectorSorting.getLocalBounds().width)/2, heightC/2 - (vectorSorting.getLocalBounds().height));

        EscExit.setFont(RobotoFont);
        EscExit.setString("Apasa \"Esc\" pentru a inchide programul");
        EscExit.setCharacterSize(24);
        EscExit.setFillColor(sf::Color(255, 255, 255));
        
        MMenu.setFont(RobotoFont);
        MMenu.setString("Apasa \"M\" pentru a ajunge in meniu");
        MMenu.setCharacterSize(24);
        MMenu.setFillColor(sf::Color(255, 255, 255));
        

        patrateMeniu.setSize(sf::Vector2f(50, 50));
        patrateMeniu.setOutlineThickness(5);
        patrateMeniu.setOutlineColor(sf::Color(255,255,255));
        patrateMeniu.setPosition(widthC/4, heightC/2);
        patrateMeniu.setFillColor(sf::Color(0,0,0,0));


        linie.setSize(sf::Vector2f(1, 1));
        linie.setPosition(widthC/100, 99*heightC/100);
        linie.setFillColor(sf::Color(255,255,255));
        // linie.setOrigin()



    }


    // The only purpose is that encapsulation can exist, go to update
    void run(){
        update();
    }

};




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