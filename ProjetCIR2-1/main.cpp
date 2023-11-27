#include "main.hpp"


int main() {

//initialisation de la fenetre:
    InitWindow(800,600,"Metro Simulator");
    int ecran= GetCurrentMonitor();
    int sw=GetMonitorWidth(ecran);
    int sh=GetMonitorHeight(ecran);
    SetWindowSize(sw,sh);
    SetTargetFPS(60);
    SetExitKey(KEY_LEFT_CONTROL);
    SetWindowPosition(0,0);

    //on ouvre le fichier txt station pour lire les stations dedans:
    std::ifstream flux("../Stations.txt");
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


        while(getline(flux, ligne)){

            std::string delimiter = ":";
            std::string name = ligne.substr(ligne.find(delimiter)+1, ligne.length()); //lecture des stations
            Station station(name, i,ligneA);
            if(200*i+35<sw) station.Coordinates={float(200*i+35),300}; //placement des coordonées pour qu'elles rentres sur l'écran
            else {
                station.Coordinates={float(200*(total_lines-i)+35),float(sh)-300}; //temporaire
            }
            ligneA.push_back(station); //ajout de la station au tableau des stations
            i++;
        }
    }
    else{
        std::cout<<"erreur lecture fichier"<<std::endl; //erreur si le fichier n'est pas lu
    }
    //Une nouvelle ère
    //un nouvel air

    for(int i=0;i<CIRCULATING_RAME;i++){
        int sens=0;
        if(i%2==0) sens=100;
        Rame rame(sens==0,i,ligneA);
        rame.vitesse=MAX_VITESSE;

        rame.Coordinates={ligneA[i%18].Coordinates.x,ligneA[i%18].Coordinates.y};
        rames.push_back(rame);
    }



    while(!WindowShouldClose()){
        global_show(ligneA,rames);
    }
    CloseWindow();

    return 1;
}
