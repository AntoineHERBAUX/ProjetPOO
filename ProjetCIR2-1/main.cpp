#include "main.hpp"


int main() {
    //on ouvre le fichier txt station pour lire les stations dedans:
    std::ifstream flux(R"(..\Stations.txt)");
    //on lit les stations dans le fichier. On sait qu'elles sont sous la forme "numéro:nom"
    std::vector<Station> ligneA;
    if(flux){
        std::string ligne;
        int i=0;
        while(getline(flux, ligne)){
            std::string delimiter = ":";
            std::string name = ligne.substr(ligne.find(delimiter)+1, ligne.length());
            Station station(name, i,ligneA);
            station.Coordinates={float(2500*i),500};
            ligneA.push_back(station);
            i++;
        }
    }
    else{
        std::cout<<"erreur"<<std::endl;
    }

    //afficher toutes les stations récupérées:
    for(int i=0; i<ligneA.size(); i++){
        std::cout<<ligneA[i].number+1   <<" "<<ligneA[i].name<<std::endl;
    }

    for(int i=0;i<CIRCULATING_RAME;i++){
        if(i%2==0){
            Rame rame(TO_4CANTONS,i,ligneA);
            rame.vitesse=MAX_VITESSE;
            ligneA[0].presentRame=&rame;
        }
        else{
            Rame rame(TO_CHU,i,ligneA);//
            rame.vitesse=0;
            ligneA[ligneA.size()-1].presentRame=&rame;
        }
    }

    return 1;
}
