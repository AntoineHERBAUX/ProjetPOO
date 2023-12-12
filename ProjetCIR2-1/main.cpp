#include "main.hpp"


int main() {

//initialisation de la fenetre:
    InitWindow(800,400,"Metro Simulator");
    int ecran= GetCurrentMonitor();
    int sw=GetMonitorWidth(ecran);
    int sh=GetMonitorHeight(ecran);
    SetWindowSize(sw,sh);
    SetTargetFPS(60);
    SetExitKey(KEY_LEFT_CONTROL);
    SetWindowPosition(0,0);

    //on ouvre le fichier txt station pour lire les stations dedans:
    std::ifstream flux("./Stations.txt");
    if(!flux){
        std::ifstream flux("../Stations.txt");
    }
    //on lit les stations dans le fichier. On sait qu'elles sont sous la forme "numéro:nom"
    std::vector<Station> ligneA;
    std::vector<Rame> rames;
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
            ////temporaire
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
        rame.vitesse=MAX_VITESSE;

        rame.Coordinates={ligneA[i%18].Coordinates.x,ligneA[i%18].Coordinates.y};
        if (rame.whichVoie == 0) {
            rame.nextStation = ligneA[i + 1 % 18];
        }
        else {rame.nextStation = ligneA[i - 1 % 18]; }
        rames.push_back(rame);
    }



    while(!WindowShouldClose()){
        for (int i = 0;i < CIRCULATING_RAME;i++) {
            rames[i].move_rame(ligneA);
        }
        global_show(ligneA,rames);
        
    }
    CloseWindow();

    return 1;
}
