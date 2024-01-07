#include <thread>
#include "main.hpp"

std::vector<Station> ligneA;
std::vector<Rame> rames;

int main() {
    SetTraceLogLevel(LOG_NONE);

//initialisation de la fenetre:
    InitWindow(800, 400, "Metro Simulator");
    Image img = LoadImage("./rame_big.png");
    SetWindowIcon(img);
    //UnloadImage(img);
    int ecran = GetCurrentMonitor();
    int sw = GetMonitorWidth(ecran);
    int sh = GetMonitorHeight(ecran);
    SetWindowSize(1600, 900);
    Image lille = LoadImage("./lille.png");
    ImageResize(&lille, 1600, 900);
    Texture2D lille_fond = LoadTextureFromImage(lille);
    UnloadImage(lille);
    SetTargetFPS(100);
    SetExitKey(KEY_LEFT_CONTROL);
    SetWindowPosition(0, 0);

    //on ouvre le fichier txt station pour lire les stations dedans:
    std::ifstream flux("./Stations.txt");
    if (!flux) {
        std::ifstream flux("../Stations.txt");
    }
    //on lit les stations dans le fichier. On sait qu'elles sont sous la forme "numéro:nom"

    if (flux) {
        std::string ligne;
        int i = 0;
        int total_lines = 0;

        while (getline(flux, ligne)) {
            total_lines++; //comptage du nombre de ligne
        }

        flux.clear(); //reset de la lecture
        flux.seekg(0, std::ios::beg);

        int mid = 1;
        int k = 1;
        int x = 0;
        int y = 0;
        while (getline(flux, ligne)) {
            if (k % 2 == 0) {
                std::string delimiter = ":";
                std::string name = ligne.substr(ligne.find(delimiter) + 1, ligne.length()); //lecture des stations
                Station station(name, i);
                station.Coordinates = {float(x), float(y)};
                ligneA.push_back(station);
                i++;
            }
            if (k % 2 == 1) {
                std::string delimiter = ":";
                x = std::stoi(ligne.substr(0, ligne.find(delimiter)));
                y = std::stoi(ligne.substr(ligne.find(delimiter) + 1, ligne.length()));
            }
            k++;




        }
    } else {
        std::cerr << "Cannot open file: " << std::strerror(errno) << std::endl;
        return EXIT_FAILURE;
        //erreur si le fichier n'est pas lu
    }
    //Une nouvelle ère
    //un nouvel air

    for (int i = 0; i < CIRCULATING_RAME; i++) {

        int sens = 0;
        if (i % 2 == 0) sens = 100;
        Rame rame(sens == 0, i, ligneA);

        Image image = LoadImage("./rame_big.png"); // Load image in CPU memory (RAM)
        ImageResize(&image, 32, 32);
        rame.image = image;
        rame.degrees = 0;

        rame.Coordinates = {ligneA[i % 18].Coordinates.x, ligneA[i % 18].Coordinates.y};
        if (rame.whichVoie == 0) {
            rame.nextStation = ligneA[i + 1 % 18];
        } else { rame.nextStation = ligneA[i - 1 % 18]; }
        rames.push_back(rame);
        //UnloadImage(image);
    }

    std::vector<std::thread> threads;
    for (auto &rame: rames) {
        threads.emplace_back(&Rame::move_rame, std::ref(rame), std::ref(ligneA));
    }

    //for (auto& thread : threads) {
    //thread.join();
    //}

    bool menu = false;
    Rame *target_rame;
    int counter=0;
    while (!WindowShouldClose()) {
        //for (int i = 0;i < CIRCULATING_RAME;i++) {
        // rames[i].move_rame(ligneA);
        //}

        //chaque station reçoit de nouveaux passagers
        if(counter%10000==0) {
            for (int i = 0; i < ligneA.size(); i++) {
                ligneA[i].new_passagers();
            }
        }
        counter++;
        counter=counter%10000;
        DrawTexture(lille_fond, -100, -100, WHITE);
        DrawFPS(200, 10);
        global_show(ligneA, rames, menu, target_rame);


        //on regarde si l'utilisateur clique sur une rame
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            for (int i = 0; i < rames.size(); i++) {
                //si il clique sur une rame, on ouvre un menu pour choisir la fonction
                if ((mouse.x < (rames[i].Coordinates.x + 50)) && (mouse.x > (rames[i].Coordinates.x - 10)) &&
                    (mouse.y < (rames[i].Coordinates.y + 20)) && (mouse.y > (rames[i].Coordinates.y - 20))) {
                    target_rame = &rames[i];
                    menu = true;
                }
            }
        }
        //si le menu est ouvert, on regarde quelle fonction l'utilisateur veut utiliser
        if (menu == true) {

            if(IsKeyPressed(KEY_ZERO)){
                std::cout<<"===================="<<std::endl;
                std::cout<<"Numero:"<<target_rame->number<<std::endl;
                std::cout<<"Vitesse:"<<target_rame->vitesse<<std::endl;
                std::cout<<"Passagers:"<<target_rame->passagers<<std::endl;
                std::cout<<"Voie:"<<target_rame->whichVoie<<std::endl;
                std::cout<<"Coordonnees:"<<target_rame->Coordinates.x<<","<<target_rame->Coordinates.y<<std::endl;
                std::cout<<"Station suivante:"<<target_rame->nextStation.name<<std::endl;
                std::cout<<"Frein d'urgence:"<<target_rame->EmergencyBrake<<std::endl;
                menu=false;
            }

            if(IsKeyPressed(KEY_ONE)){
                target_rame->EmergencyBrake=true;
                menu=false;
            }
            if(IsKeyPressed(KEY_TWO)){
                std::vector<Station>::iterator it;
                //utilisation d'une lambda pour la comparaison. Elle compare les coordonées des stations
                it = std::find_if(ligneA.begin(), ligneA.end(), [target_rame](Station const& s) { return s.Coordinates==target_rame->nextStation.Coordinates; });
                if(it!=ligneA.end()){
                    target_rame->nextStation=*(it+1);
                }
                menu=false;
            }
            if(IsKeyPressed(KEY_THREE)){
                if(target_rame->vitesse==0){
                    target_rame->passagers=0;
                }
                else{
                    std::cout<<"La rame est en mouvement, vous ne pouvez pas vider la rame"<<std::endl;
                }
                menu=false;
            }
            if(IsKeyPressed(KEY_FOUR)){
                target_rame->EmergencyBrake=false;;
                menu=false;
            }
            if(IsKeyPressed(KEY_FIVE)){
                menu=false;
            }
        }
        }

        UnloadImage(img);
        UnloadTexture(lille_fond);

        CloseWindow();

        return 1;
    }
