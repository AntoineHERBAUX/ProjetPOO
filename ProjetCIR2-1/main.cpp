#include <thread>
#include "main.hpp"

std::vector<Station> ligneA;
std::vector<Rame> rames;

int main() {
    SetTraceLogLevel(LOG_NONE);

//initialisation de la fenetre:
    InitWindow(800,400,"Metro Simulator");
    Image img = LoadImage("./rame_big.png");
    SetWindowIcon(img);
    //UnloadImage(img);
    int ecran= GetCurrentMonitor();
    int sw=1400;
    int sh=800;
    SetWindowSize(sw,sh);
    Image lille = LoadImage("./lille.png");
    ImageResize(&lille, 1600, 900);
    Texture2D lille_fond = LoadTextureFromImage(lille);
    UnloadImage(lille);
    SetTargetFPS(100);
    SetExitKey(KEY_LEFT_CONTROL);
    SetWindowPosition(0,0);

    //on ouvre le fichier txt station pour lire les stations dedans:
    std::ifstream flux("./Stations.txt");
    if(!flux){
        std::ifstream flux("../Stations.txt");
    }
    //on lit les stations dans le fichier. On sait qu'elles sont sous la forme "numéro:nom"

    if(flux){
        std::string ligne;
        int i=0;
        int total_lines=0;

        while(getline(flux, ligne)){
            total_lines++; //comptage du nombre de ligne
        }

        flux.clear(); //reset de la lecture
        flux.seekg(0, std::ios::beg);

        int mid = 1;
        int k = 1;
        int x=0;
        int y=0;
        while(getline(flux, ligne)){
            if (k % 2 == 0) {
                std::string delimiter = ":";
                std::string name = ligne.substr(ligne.find(delimiter) + 1, ligne.length()); //lecture des stations
                Station station(name, i);
                station.Coordinates = { float(x), float(y) };
                ligneA.push_back(station);
                i++;
            }
            if (k % 2 == 1) {
                std::string delimiter = ":";
                x = std::stoi(ligne.substr(0, ligne.find(delimiter) ));
                y = std::stoi(ligne.substr(ligne.find(delimiter)+1, ligne.length()));
            }
            k++;


            
            //if (150 * i + 60 < (sw)) {
            //    station.Coordinates = { float(150 * i + 60),float(200) };
            // //placement des coordonées pour qu'elles rentres sur l'écran
            //}
            //else if(mid==1) {
            //    station.Coordinates = { float(150 * (i - 1) + 60),float(400) };
            //    mid = 0;
            //}
            //else{
            //    station.Coordinates = { float(150 * (total_lines - i-1) + 60),float(sh) - 200 };
            //temporaire
            //}
            //ligneA.push_back(station); //ajout de la station au tableau des stations
            //i++;
        }
    }
    else{
        std::cerr << "Cannot open file: " << std::strerror(errno) << std::endl;
        return EXIT_FAILURE;
        //erreur si le fichier n'est pas lu
    }
    //Une nouvelle ère
    //un nouvel air

    for(int i=0;i<CIRCULATING_RAME;i++){
        
        int sens=0;
        if(i%2==0) sens=100;
        Rame rame(sens==0,i,ligneA);

        Image image = LoadImage("./rame_big.png"); // Load image in CPU memory (RAM)
        ImageResize(&image, 32, 32);
        rame.image = image;   
        rame.degrees = 0;

        rame.Coordinates={ligneA[i%18].Coordinates.x,ligneA[i%18].Coordinates.y};
        if (rame.whichVoie == 0) {
            rame.nextStation = ligneA[i + 1 % 18];
        }
        else {rame.nextStation = ligneA[i - 1 % 18]; }
        rames.push_back(rame);
        //UnloadImage(image);
    }

    std::vector<std::thread> threads;
    for (auto& rame : rames) {
        threads.emplace_back(&Rame::move_rame, std::ref(rame), std::ref(ligneA));
    }

    //for (auto& thread : threads) {
      //thread.join();
    //}

    bool menu=false;
    int counter=0;
    Rame* target_rame;
    while(!WindowShouldClose()){
        if (counter%1000==0){
            for(int i=0; i<ligneA.size();i++){
                ligneA[i].new_passagers();
            }
        }
        counter++;
        counter%=1000;

        //quand on clique sur une rame passe menu en true
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            for(int i=0;i<rames.size();i++){
                if(CheckCollisionPointRec(GetMousePosition(),{rames[i].Coordinates.x,rames[i].Coordinates.y,50,20})){
                    menu=true;
                    target_rame=&rames[i];
                }
            }
        }
        if(menu==true){

            if(IsKeyPressed(KEY_ZERO)){
                menu=false;
                std::cout<<"===================="<<std::endl;
                std::cout<<"Rame numéro "<<target_rame->number<<std::endl;
                std::cout<<"Vitesse: "<<target_rame->vitesse<<std::endl;
                std::cout<<"Passagers: "<<target_rame->passagers<<std::endl;
                std::cout<<"Prochaine station: "<<target_rame->nextStation.name<<std::endl;
                std::cout<<"Frein d'urgence: "<<target_rame->EmergencyBrake<<std::endl;
                std::cout<<"===================="<<std::endl;

            }
            if(IsKeyPressed(KEY_ONE)){
                target_rame->EmergencyBrake=true;

                menu=false;
            }
            if(IsKeyPressed(KEY_TWO)){
                target_rame->nextStation=ligneA[target_rame->nextStation.number+1];
                menu=false;
            }
            if(IsKeyPressed(KEY_THREE)){
                if(target_rame->vitesse==0){
                    target_rame->passagers=0;
                }
                else{
                    std::cout<<"La rame est en mouvement, impossible de vider les passagers"<<std::endl;
                }
                menu=false;
            }
            if(IsKeyPressed(KEY_FOUR)){
                if(target_rame->EmergencyBrake==true){
                    target_rame->EmergencyBrake=false;
                }
                else{
                    std::cout<<"La rame n'est pas en arrêt d'urgence"<<std::endl;
                }
                menu=false;
            }
            if(IsKeyPressed(KEY_FIVE)){
                menu=false;
            }
        }


        DrawTexture(lille_fond, -100, -100, WHITE);
        DrawFPS(200,10);
        global_show(ligneA,rames, menu, target_rame);

    }
    UnloadImage(img);
    UnloadTexture(lille_fond);
    
    CloseWindow();

    return 1;
}
