#include "HeaderClass.h"


game::game(int width_, int height_) : mwindow(sf::VideoMode(width_, height_), "VectorSorting", sf::Style::None ) {
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


        linie.setSize(sf::Vector2f(1, 1));
        linie.setPosition(widthC/100, 99*heightC/100);
        linie.setFillColor(sf::Color(255,255,255));
        // linie.setOrigin()


}



void game::run(){
    update();
    // The only purpose is that encapsulation can exist, go to update
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !! Doar cele doua functii de deasupra sunt publice !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


void game::renderer(){
    return;
}





void game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
        if (key == sf::Keyboard::Escape){
            mwindow.close();
        }
        if (key == sf::Keyboard::M){
            whichMode = 1;
        }    

        if (key == sf::Keyboard::Num1){
            whichMode = 11;
        }

        if (key == sf::Keyboard::Num2){
            whichMode = 12;
        }

        return;
    }







void game::processEvents(){
    
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







void game::update(){
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



            case 11:
                SelectionSort();
                whichMode=1;
            break;


            case 12:
                BubbleSort();
                whichMode=1;
            break;

            
        }

        mwindow.display();


        
    }
    }






void game::vectorInit(){

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








void game::VectorOutputFunction(){
    mwindow.clear();
    int inaltimeLinie;
    for(int i=1;i<=limita;i++){           
        inaltimeLinie = vector[i]*5;
        linie.setSize(sf::Vector2f(1,inaltimeLinie));
        
        
        linie.setPosition(widthC/100 + i * 10, heightC-heightC/10-inaltimeLinie); 
        // aparent cand se afiseaza, se afiseaza din dreapta sus
        // de aceea trebuie sa ne asiguram de la inaltime afisam
        // de la inaltimea maxima - inaltimeLinie ( inaltimeLinie fiind inaltimea fiecarei linii)
        
        // switch(culori[i]){
        //     case 1:
        //     linie.setFillColor(sf::Color(255,255,255));
        //     break;

        //     case 2:
        //     linie.setFillColor(sf::Color(0, 255, 0));
        //     break;

        //     case 3:
        //     linie.setFillColor(sf::Color(255, 0, 0));
        //     break;

        //     case 4:
        //     linie.setFillColor(sf::Color(0, 0, 255));
        //     break;

        // }

        mwindow.draw(linie);
    }
    mwindow.display();
    return;
}
void game::SelectionSort(){
    
    limita = 100;
    vectorInit(); // initializeaza vectorul "vector", impreuna cu vectorul "culori"


    for(int i=1;i<limita;i++)
        for(int j=i+1;j<=limita;j++){
            processEvents();
            
            if( !(mwindow.isOpen()) || whichMode!=11 ) //if the window is not open
                goto InsertionClosed;

            if(vector[i]>vector[j]){
                std::swap(vector[i], vector[j]);
                VectorOutputFunction();
            }
        }

        InsertionClosed:
        return;
    }



    void game::BubbleSort(){
        vectorInit();
        bool sortat=0;

        do{
            processEvents();
            if(!(mwindow.isOpen()) || whichMode!=12)
                goto BubbleClosed;
            sortat=0;
            for(int i=1;i<limita;i++){
                if(vector[i]>vector[i+1]){
                    std::swap(vector[i], vector[i+1]);
                    sortat=1;
                    VectorOutputFunction();
                }
            }


        }while(sortat==1);

        BubbleClosed:
        return;
    }



    

    void game::changeColorsMode(int mode, int indice){
        // mode:
        // 1 - alb (nefolosit)
        // 2 - verde (in comparatie)
        // 3 - rosu (comparatie nereusita)
        // 4 - albastru (schimbare)

        // indice: reprezinta indicele din vector care trebuie schimbat

        culori[indice]=mode;

        return;
    }
    