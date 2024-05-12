#include "HeaderClass.h"


game::game(int width_, int height_) : mwindow(sf::VideoMode(width_, height_), "VectorSorting", sf::Style::None ) {
        widthC = width_;
        heightC = height_;

        limita=100;


        timeSinceLastUpdate = sf::Time::Zero;
    
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


        linie.setSize(sf::Vector2f(5, 1));
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
        
        
        processEvents();
        mwindow.clear();




        // DEBUG
        // TimePerFrame = 0.016666
        // 1000 - 1 secunda
        // 100 - 0.1 secunde
        // 10 - 0.01 secunde
        // Sleep( 100 );  
        // std::cerr << timeSinceLastUpdate.asSeconds() <<' ' << TimePerFrame.asSeconds() << '\n';
        // DEBUG
        
        // Se misca incet pentru ca TimePerFrame este mare. Ar trebui sa fie mai mic decat 1/60 fps (0.0166).
        

        FPSIncreaser:
        timeSinceLastUpdate += clock.restart();
        if (timeSinceLastUpdate <= TimePerFrame){
            processEvents();
            goto FPSIncreaser;
        }
        timeSinceLastUpdate=sf::Time::Zero;




        switch(whichMode){
            case 0:
                if(opacityVectorSorting<255){
                    opacityVectorSorting+=1.f;
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



void game::WaitDisplayVector(){
    int modeRightNow=whichMode;
    while(mwindow.isOpen() && modeRightNow==whichMode){
        
    


        processEvents();
        VectorOutputFunction();
    }

    return;
}




void game::VectorOutputFunction(){
    mwindow.clear();
    int inaltimeLinie;
    for(int i=1;i<=limita;i++){           
        inaltimeLinie = vector[i]*5;
        linie.setSize(sf::Vector2f(linie.getSize().x,inaltimeLinie));
        
        
        linie.setPosition(widthC/100 + i * 10, heightC-heightC/10-inaltimeLinie); 
        // aparent cand se afiseaza, se afiseaza din dreapta sus
        // de aceea trebuie sa ne asiguram de la inaltime afisam
        // de la inaltimea maxima - inaltimeLinie ( inaltimeLinie fiind inaltimea fiecarei linii)
        
        switch(culori[i]){

        // 1 - alb (nefolosit)
        // 2 - rosu (comparatie nereusita)
        // 3 - verde (comparatie reusita)
        // 4 - albastru (indicele se muta la alta locatie. Se foloseste cand cel cu care isi schimba pozitia si-a gasit locul)
        
            case 1:
            linie.setFillColor(sf::Color(255,255,255));
            break;

            case 2:
            linie.setFillColor(sf::Color(255, 0, 0));
            break;

            case 3:
            linie.setFillColor(sf::Color(0, 255, 0));
            break;

            case 4:
            linie.setFillColor(sf::Color(0, 0, 255));
            break;

        }

        mwindow.draw(linie);
    }
    mwindow.display();
    return;
}
void game::SelectionSort(){
    

    vectorInit();

    int iTrecut=0;
    int jTrecut=0;
    // Au rolul de a ajuta in colorarea vectorului
    // adica voi lasa un numar de iteratii sa mearga cu o anumita culoare
    // desi pentru cazul in care se schimba mai multe culori... se complica

    for(int i=1;i<limita;i++)
        for(int j=i+1;j<=limita;j++){



            // TIMPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
            FPSIncreaser:
            timeSinceLastUpdate += clock.restart();
            if (timeSinceLastUpdate <= TimePerFrame){
                processEvents();
                goto FPSIncreaser;
            }
            timeSinceLastUpdate=sf::Time::Zero;
            // TIMPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP


            processEvents();
            


            if( !(mwindow.isOpen()) || whichMode!=11 ) //if the window is not open
                goto SelectionClosed;
            
            culori[iTrecut]=1;
            culori[jTrecut]=1;
            if(vector[i]>vector[j]){
                iTrecut=i;
                jTrecut=j;
                culori[i]=4;
                culori[j]=3;

                std::swap(vector[i], vector[j]);
            }
            else{
                iTrecut=i;
                jTrecut=j;
                culori[i]=2;
                culori[j]=2;
            }
            VectorOutputFunction();
        }

        culori[iTrecut]=1;
        culori[jTrecut]=1;

        WaitDisplayVector();

        SelectionClosed:
        return;
    }



    void game::BubbleSort(){
        vectorInit();
        bool sortat=0;

        int iTrecut=0;
        int iPlusUnuTrecut=0;

        do{


            //TIMPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP            
            FPSIncreaser:
            timeSinceLastUpdate += clock.restart();
            if (timeSinceLastUpdate <= TimePerFrame){
                processEvents();
                goto FPSIncreaser;
            }
            timeSinceLastUpdate=sf::Time::Zero;
            //TIMPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP            
            processEvents();


            if(!(mwindow.isOpen()) || whichMode!=12)
                goto BubbleClosed;

            
            sortat=0;
            for(int i=1;i<limita;i++){
                if(vector[i]>vector[i+1]){
                    std::swap(vector[i], vector[i+1]);
                    sortat=1;

                    culori[iTrecut]=1;
                    culori[iPlusUnuTrecut]=1;
                    iTrecut=i;
                    iPlusUnuTrecut=i+1;
                    culori[i]=3;
                    culori[i+1]=3;

                }
                else{
                    culori[iTrecut]=1;
                    culori[iPlusUnuTrecut]=1;                    
                    culori[i]=2;
                    culori[i+1]=2;
                    iTrecut=i;
                    iPlusUnuTrecut=i+1;
                }
                
                VectorOutputFunction();
            }


        }while(sortat==1);
        
        culori[iTrecut]=1;  
        culori[iPlusUnuTrecut]=1;  

        WaitDisplayVector();
        BubbleClosed:
        return;
    }



    

    void game::changeColorsMode(int mode, int indice){
        // mode:
        // 1 - alb (nefolosit)
        // 2 - rosu (comparatie nereusita)
        // 3 - verde (comparatie reusita)
        // 4 - albastru (indicele se muta la alta locatie. Se foloseste cand cel cu care isi schimba pozitia si-a gasit locul)

        // indice: reprezinta indicele din vector care trebuie schimbat

        culori[indice]=mode;

        return;
    }
    