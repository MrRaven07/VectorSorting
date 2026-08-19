#include "../include/HeaderClass.h"

game::game(int width_, int height_) : mwindow(sf::VideoMode(width_, height_), "VectorSorting", sf::Style::None )  {


        widthC = width_;
        heightC = height_;
        

        if (!icon.loadFromFile("assets/icon/VectorSorting256x256.png")) {
            std::cerr<<"EROAREICONITA\n";
        }
        mwindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


        TimePerFrame=sf::seconds(1.f / 60.f);

        /*
        0, 0  -> seteaza inceputul view-ului (in cazul asta coltul din stanga sus)
        widthC, heightC -> seteaza latimea si inaltimea view-ului
        */

        isFull=0;
        screenWidth = sf::VideoMode::getDesktopMode().width;
        screenHeight = sf::VideoMode::getDesktopMode().height;
        
        fullscreenNormalRatio.x=1;
        fullscreenNormalRatio.y=1;

        if (!buffer.loadFromFile("assets/sounds/bip.wav"))
        {
            std::cerr << "EROAREAUDIO\n";
        }
        sonor = 10.f;
        bipS.setBuffer(buffer);
        bipS.setVolume(sonor);
        normalPitch = bipS.getPitch(); // care e 1

        limita=100;
        inaltimeFraction=0.7;
        latimeLinie=5;


    
        if (!RobotoFont.loadFromFile("assets/fonts/Roboto-Regular.ttf"))
            std::cerr << "Nu merge fisierul";


            
        vectorSorting.setFont(RobotoFont);
        vectorSorting.setString(L"Tipuri de sortări");
        vectorSorting.setCharacterSize(50); 
        vectorSorting.setFillColor(sf::Color(255, 255, 255, 0));
        vectorSorting.setPosition(widthC/2 - (vectorSorting.getLocalBounds().width)/2, heightC/2 - (vectorSorting.getLocalBounds().height));





        EscExit.setFont(RobotoFont);
        EscExit.setString(L"Apasă \"Esc\" pentru a închide programul");
        EscExit.setCharacterSize(24);
        EscExit.setFillColor(sf::Color(255, 255, 255));
        
        MMenu.setFont(RobotoFont);
        MMenu.setString(L"Apasă Tastele:\n\"M\" pentru a ajunge în meniul actual \nF11 pentru a face fereastra Fullscreen\nFolosiți Scroll-ul Mouse-ului pentru a derula \nmai încet sau mai rapid programul\n1 pentru a vedea Selection Sort \n2 pentru a vedea Bubble Sort \n3 pentru a vedea Insertion Sort \n4 pentru a vedea Binary Insertion Sort \n5 pentru a vedea Merge Sort");
        MMenu.setCharacterSize(24);
        MMenu.setFillColor(sf::Color(255, 255, 255));
        
        EscExit.setPosition(widthC-EscExit.getLocalBounds().width, 0);
        MMenu.setPosition(0, 0);


        FPSText.setFont(RobotoFont);
        FPSText.setCharacterSize(24);
        FPSText.setFillColor(sf::Color(255,255,255));
        FPSText.setPosition(widthC*0.5, heightC*0.01);


        numarSortari=5;
        patrateMeniuDimensiune.x=50;
        patrateMeniuDimensiune.y=50;
        patrateMeniu.setSize(patrateMeniuDimensiune);
    
        sf::Vector2i pozitiePatratInceput(widthC / 2.5, heightC / 3);
        patrateMeniu.setFillColor(sf::Color(255,255,255));
        for(int i=0;i<numarSortari;i++){
            patrateMeniuVector[i].x=pozitiePatratInceput.x + i * 60;
            patrateMeniuVector[i].y=pozitiePatratInceput.y;
        }
        PatrateTextSFML.setFont(RobotoFont);
        PatrateTextSFML.setCharacterSize(24);
        PatrateTextSFML.setPosition(widthC*0.05, heightC*0.75);
        PatrateTextSFML.setFillColor(sf::Color(255, 255, 255));


        linie.setFillColor(sf::Color(255,255,255));
        // linie.setOrigin()


        CeSortareText.setFont(RobotoFont);
        //CeSortareText.setString(CeSortare Matrice);
        CeSortareText.setCharacterSize(24);
        CeSortareText.setFillColor(sf::Color(255, 255, 255));
    


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
        mwindow.clear(sf::Color::Black);
    }    

    if (key == sf::Keyboard::Num1){
        whichMode = 11; // SelectionSort
    }

    if (key == sf::Keyboard::Num2){
        whichMode = 12; // BubbleSort
    }

    if (key == sf::Keyboard::Num3){
        whichMode = 13; // InsertionSort
    }

    if (key == sf::Keyboard::Num4){
        whichMode = 14; // BinaryInsertionSort
    }

    if (key == sf::Keyboard::Num5){
        whichMode = 15; // MergeSort
    }

    if(key == sf::Keyboard::F11){
        ToggleFullscreen();
    }
    
    if(key == sf::Keyboard::Z){
        ToggleMute();
    }
    return;
}

void game::ToggleMute(){
    isMuted= !(isMuted);
    if(isMuted==1){
        bipS.setVolume(0.f);
    }
    if(isMuted==0){
        bipS.setVolume(5.f);
    }
}

void game::PlayBip(int ii){
    bipS.setPitch(normalPitch+(ii/100.f));
    bipS.play();  
    return;
}


// Functie pentru a comuta intre modurile fullscreen/windowed
void game::ToggleFullscreen() {
    isFull = !(isFull);
    
    if(isFull==1){
        mwindow.setPosition(sf::Vector2i(0, 0));
        mwindow.setSize(sf::Vector2u(screenWidth, screenHeight));

        fullscreenNormalRatio.x = 1.f*screenWidth/widthC;
        fullscreenNormalRatio.y = 1.f*screenHeight/heightC;
        

    }
    if(isFull==0){
        mwindow.setPosition(sf::Vector2i(curPositionX, curPositionY));
        mwindow.setSize(sf::Vector2u(widthC, heightC));

        fullscreenNormalRatio.x = 1;
        fullscreenNormalRatio.y = 1;
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

            // case sf::Event::KeyReleased:
            //     handlePlayerInput(event.key.code, false);
            //     break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Middle) {
                    TimePerFrame=sf::seconds(1.f / 60.f);
                }
                
                if(whichMode!=1) // daca nu se afla in meniu
                    break;
                MouseCheckMeniu(event.mouseButton.x, event.mouseButton.y, 1);
            break;

            break;
            case sf::Event::MouseWheelScrolled:
                int secToMicro=1e6; // 1 second = 1e6 microseconds
                short int delta = (event.mouseWheelScroll.delta < 0) ? 1 : -1;

                float FPSPrezent = 1/TimePerFrame.asSeconds();
                float adjustTime = (secToMicro / FPSPrezent / FPSPrezent); 
                
                adjustTime = adjustTime * delta;
                int timpFinal = TimePerFrame.asMicroseconds()+adjustTime;
                if(0<timpFinal && timpFinal<=1000000)
                    TimePerFrame = sf::microseconds(timpFinal);
                
            break;  


        }

        if(whichMode==1){
            sf::Vector2i mousePosition = sf::Mouse::getPosition(mwindow);
            MouseCheckMeniu(mousePosition.x, mousePosition.y, 0);
        }
    }
}



void game::MouseCheckMeniu(int mouseX, int mouseY, bool click){

    /*
    Imi pare rau pentru variabila fullscreenNormalRatio, insa, cand se face fullscreen, se schimba ratio-ul
    si trebuie sa se in considerare pentru coliziunea mouseului cu patratele
    */
    if(patrateMeniuVector[0].x * fullscreenNormalRatio.x <=mouseX && 
    mouseX <= ( (patrateMeniuVector[numarSortari-1].x + patrateMeniuDimensiune.x )*fullscreenNormalRatio.x )&& //-1 pentru ca lista incepe de la 0
    patrateMeniuVector[0].y * fullscreenNormalRatio.y<=mouseY && 
    mouseY <= ((patrateMeniuVector[numarSortari-1].y + patrateMeniuDimensiune.y)*fullscreenNormalRatio.y)
    )
    {   
        
        for(int i=0;i<numarSortari;i++){
            if(patrateMeniuVector[i].x * fullscreenNormalRatio.x <= mouseX &&
            mouseX <= ( (patrateMeniuVector[i].x + patrateMeniuDimensiune.x) * fullscreenNormalRatio.x )
            )
            {
                PatrateTextState=1+i; // +1 pentru ca i incepe de la 0, iar prima sortare este la pozitia 11
                
                if(click==1){
                    whichMode= 10 + 1 + i;
                    PatrateTextState=0;
                    goto MouseCheckMeniuClosed;
                }
                goto MouseCheckMeniuClosed;
            }
        }
    }
    PatrateTextState=0;
    MouseCheckMeniuClosed:
    return;
}



void game::update(){
        
        while(mwindow.isOpen()){

        mwindow.clear();


        WaitingTime(); // for fps

        switch(whichMode){
            case 0:
                if(opacityVectorSorting<255)
                    opacityVectorSorting+=3.f;
                else  
                    whichMode=1;
                vectorSorting.setFillColor(sf::Color(255,255,255,int(opacityVectorSorting)));
                mwindow.draw(vectorSorting);
            break;

            case 1: // menu
            
                ShowFPSText();
                mwindow.draw(MMenu);
                mwindow.draw(EscExit);

                patrateMeniu.setPosition(widthC/2, heightC/2);

                for(int i=0;i<numarSortari;i++){
                    patrateMeniu.setPosition(patrateMeniuVector[i].x, patrateMeniuVector[i].y);
                    mwindow.draw(patrateMeniu);
                }
                PatrateTextSFML.setString(PatrateText[PatrateTextState]);
                mwindow.draw(PatrateTextSFML);

                
            break;

            case 2:

            break;

            case 11:
                SelectionSort();
            break;


            case 12:
                BubbleSort();
            break;

            case 13:
                InsertionSort();
            break;

            case 14:
                BinaryInsertionSort();
            break;

            case 15:
                MergeSort();
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
        
        int initialMode = whichMode;
        float adjustRandomizare = 0.5f;

        // Randomizarea
        for(int i=1;i<=limita;i++){
            std::swap(vector[i], vector[rand()%limita+1]);
            WaitingTime(adjustRandomizare);
            VectorOutputFunction();
            if(initialMode!=whichMode)
                goto VectorInitClosed;
        }


        VectorInitClosed:
        return;
    }



void game::WaitDisplayVector(int modeRightNow){
    int ii=1;
    while(mwindow.isOpen() && modeRightNow == whichMode){
        WaitingTime();
        if(ii<=limita){
            culori[ii++]=3;
            PlayBip(ii);
            VectorOutputFunction();
        }
        processEvents();
    }

    return;
}



void game::WaitingTime(float adjustTime){
    // DEBUG
    // TimePerFrame = 0.016666 respectiv 1/60
    // 1000 - 1 secunda
    // 100 - 0.1 secunde
    // 10 - 0.01 secunde
    // Sleep( 100 );  
    // std::cerr << timeSinceLastUpdate.asSeconds() <<' ' << TimePerFrame.asSeconds() << '\n';
    // DEBUG
    
    sf::Time localTimePerFrame = sf::seconds(TimePerFrame.asSeconds()*adjustTime);
    // The bigger the number, the slower, 
    // 1/30 > 1/60
    // 30 -> mai putine fps-uri -> mai incet  
    // 60 -> mai multe fps-uri -> mai rapid
    
    sf::Time timeSinceLastUpdate;
    timeSinceLastUpdate = sf::Time::Zero;


    // TIMPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
    FPSIncreaser:
    processEvents();
    timeSinceLastUpdate += clock.restart();
    if (timeSinceLastUpdate <= localTimePerFrame){
        processEvents();
        goto FPSIncreaser;
    }
    timeSinceLastUpdate=sf::Time::Zero;
    // TIMPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP

    return;
}

void game::ShowFPSText(){
    FPSText.setString(std::to_string(1/TimePerFrame.asSeconds()));
    mwindow.draw(FPSText);
}


void game::VectorOutputFunction(){
    mwindow.clear();
    ShowFPSText();

    int tallness;
    int farLeft=0;
    int mijlocVector=limita/2;
    int farRight=limita;
    int distantaIntrePeretiiDinStanga = 10; 


    for(int i=1;i<=limita;i++){           
        tallness = vector[i] * (heightC / 125) * inaltimeFraction;
        linie.setSize(sf::Vector2f( latimeLinie , tallness ));
        linie.setPosition( ( widthC/2 - distantaIntrePeretiiDinStanga * limita/2 ) + i * distantaIntrePeretiiDinStanga , (heightC * 9 / 10)-tallness); 
        
        switch(culori[i]){
            case 1: // alb
            linie.setFillColor(sf::Color(255,255,255));
            break;

            case 2:// rosu
            linie.setFillColor(sf::Color(255, 0, 0));
            break;

            case 3: // verde
            linie.setFillColor(sf::Color(0, 255, 0));
            break;

            case 4: // albastru
            linie.setFillColor(sf::Color(0, 0, 255));
            break;

            case 5: // portocaliu
            linie.setFillColor(sf::Color(255, 94, 0));
            break;

            case 6: // albastru inchis deschis
            linie.setFillColor(sf::Color(66, 88, 255));
            break;

            case 7: // albastru deschis
            linie.setFillColor(sf::Color(0, 255, 225));
            break;
        }
        CeSortareText.setString(CeSortare[whichMode-10]);
        CeSortareText.setPosition(widthC/2 - (CeSortareText.getLocalBounds().width / 2 ) , heightC - ( CeSortareText.getLocalBounds().height*2 ) );
        mwindow.draw(CeSortareText);
        mwindow.draw(linie);
    }
    mwindow.display();
    return;
}

void game::AssignCulori(int ii, int icol, int jj, int jcol){
    static int iTrecut;
    static int jTrecut;

    culori[iTrecut]=1;
    culori[jTrecut]=1;

    culori[ii]=icol;
    culori[jj]=jcol;
    PlayBip(ii);
    PlayBip(jj);

    iTrecut=ii;
    jTrecut=jj;

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

            WaitingTime(); // for fps
            

            if( !(mwindow.isOpen()) || whichMode!=11 ) //if the window is not open
                goto SelectionClosed;
            
            // culori[iTrecut]=1;
            // culori[jTrecut]=1;
            if(vector[i]>vector[j]){
                // iTrecut=i;
                // jTrecut=j;
                // culori[i]=3;
                // culori[j]=3;
                AssignCulori(i, 3, j, 3);


                std::swap(vector[i], vector[j]);
            }
            else{
                // iTrecut=i;
                // jTrecut=j;
                // culori[i]=2;
                // culori[j]=2;
                AssignCulori(i, 2, j, 2);
            }
            VectorOutputFunction();
        } 

        AssignCulori(0, 1, 0, 1);


        WaitDisplayVector(11);

        whichMode=1; // revenire din planul oniric

        SelectionClosed:
        return;
    }



    void game::BubbleSort(){
        vectorInit();
        bool sortat=0;
        int newLimit=limita; // se creeaza asta, deorece stim ca dupa fiecare iterare, vectorul trerbuie sa compare cu macar 1 mai putin
        int iTrecut=0;
        int iPlusUnuTrecut=0;

        do{

            sortat=0;
            for(int i=1;i<newLimit;i++){
                if(!(mwindow.isOpen()) || whichMode!=12)
                    goto BubbleClosed;
                    WaitingTime(); // for fps
    

                    if(vector[i]>vector[i+1]){
                        std::swap(vector[i], vector[i+1]);
                        sortat=1;

                        // culori[iTrecut]=1;
                        // culori[iPlusUnuTrecut]=1;
                        // iTrecut=i;
                        // iPlusUnuTrecut=i+1;
                        // culori[i]=3;
                        // culori[i+1]=3;

                        AssignCulori(i, 3, i+1, 3);

                    }
                    else {
                        // culori[iTrecut]=1;
                        // culori[iPlusUnuTrecut]=1;                    
                        // culori[i]=2;
                        // culori[i+1]=2;
                        // iTrecut=i;
                        // iPlusUnuTrecut=i+1;
                        AssignCulori(i, 2, i+1, 2);

                    }
                
                VectorOutputFunction();
            }


            newLimit--;
        }while(sortat==1);
        
        AssignCulori(0, 1, 0, 1);


        WaitDisplayVector(12);

        whichMode=1;
        BubbleClosed:
        return;
    }



    void game::InsertionSort(){
        vectorInit();

        int jTrecut=0, jPlusUnuTrecut=0;
        
        for(int i=2;i<=limita;i++){
            int j,key;
            key = vector[i];
            j = i - 1;

            while(j >= 1 && vector[j]>key){
                if(!(mwindow.isOpen()) || whichMode!=13)
                    goto InsertionClosed;

                vector[j+1]=vector[j];

                // culori[jTrecut]=1;                
                // culori[jPlusUnuTrecut]=1;                
                // culori[j]=3;
                // culori[j+1]=3;
                // jTrecut=j;
                // jPlusUnuTrecut=j+1;

                AssignCulori(j, 3, j+1, 3);

                j = j - 1;
                WaitingTime();
                VectorOutputFunction();
            }
            // culori[jTrecut]=1;                
            // culori[jPlusUnuTrecut]=1;   
            // culori[j] = 2;
            // culori[j+1] = 2;
            // jTrecut=j;
            // jPlusUnuTrecut=j+1;

            AssignCulori(j, 2, j+1, 2);

            WaitingTime();
            VectorOutputFunction();


            vector[j+1]=key;
        
        }

        WaitDisplayVector(13);
        whichMode=1; // revenire din planul oniric
        InsertionClosed:
        return;
    }



    void game::BinaryInsertionSort(){
        vectorInit();

        int midTrecut=0;
        
        if(!(mwindow.isOpen()) || whichMode!=14){
            goto BinInsertionClosed;
        }

        for(int i=2;i<=limita;i++){
            WaitingTime();

            if(!(mwindow.isOpen()) || whichMode!=14)
                goto BinInsertionClosed;
            int j=i-1,key;
            int loc;            

            int item = vector[i];
            int low=0, high=j;
            

            // Binary Search
            while (low <= high) {
                culori[midTrecut]=1;

                if(!(mwindow.isOpen()) || whichMode!=14)
                    goto BinInsertionClosed;

                int mid = low + (high - low) / 2;
            

                if (item == vector[mid]){
                    loc = mid + 1;
                    goto endSearch;
                }
                else if (item > vector[mid])
                    low = mid + 1;
                else
                    high = mid - 1;
                
                culori[mid]=7;
                AssignCulori(low, 5, high, 6);
                midTrecut = mid;
                
                WaitingTime();
                VectorOutputFunction();

            }
            AssignCulori(0, 1, 0, 1);
            PlayBip(j);
            loc = low;
            endSearch:
            // Binary Search

            while(j >= loc) {
                vector[j+1] = vector[j];
                j--;
            }


            vector[j+1] = item;

            WaitingTime();
            VectorOutputFunction();

        }

        culori[1]=1;
        WaitDisplayVector(14);

        BinInsertionClosed:
        return;
    }




    void game::MergeSort(){
        vectorInit();
        WaitingTime();
        int tmp[1234];
        MergeSortRecursiv(tmp, 1, limita);

        WaitDisplayVector(15);
        whichMode=1; // revenire din planul oniric
        
        return;
    }

    void game::MergeSortRecursiv(int tmp[], int st, int dr){
        if(st < dr) {
    
            WaitingTime();
            int m = (st + dr) / 2;

                if(!(mwindow.isOpen()) || whichMode!=15)
                    goto MergeSortClosed;

            MergeSortRecursiv(tmp, st , m);

                if(!(mwindow.isOpen()) || whichMode!=15)
                    goto MergeSortClosed;

            MergeSortRecursiv(tmp, m + 1 , dr);

                if(!(mwindow.isOpen()) || whichMode!=15)
                    goto MergeSortClosed;

            //Interclasare
            int i = st, j = m + 1, k = 0;

            while( i <= m && j <= dr ){
                if(vector[i] < vector[j]){
                    tmp[++k] = vector[i++];
                    AssignCulori(i, 3, j, 1);
                }
                else{
                    tmp[++k] = vector[j++];
                    AssignCulori(i, 1, j, 2);
                }

                WaitingTime();
                VectorOutputFunction();
                
            }
            AssignCulori(0, 1, 0, 1);

            while(i <= m)
                tmp[++k] = vector[i++];

            while(j <= dr)
                tmp[++k] = vector[j++];

            for(i = st , j = 1 ; i <= dr ; i ++ , j ++)
                vector[i] = tmp[j];
            
            

	    }
        MergeSortClosed:
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
    