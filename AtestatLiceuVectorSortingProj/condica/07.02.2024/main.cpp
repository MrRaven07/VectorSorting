#include <iostream>
#include <SFML/Graphics.hpp>

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

    9 KILL PROGRAM     
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




    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
        if (key == sf::Keyboard::Escape){
            whichMode = 9;
            // exit = 1;
        }
        if (key == sf::Keyboard::M){
            whichMode = 1;
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
                    //opacityVectorSorting+=0.025f;

                }
                else {
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


            case 9:

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

    game Game(widthS, heightS);
    
    Game.run();

    // sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");


    

    return 0;
}