#include "main.hpp"


int main() {
    std::vector<Station> ligneA;
    //on ouvre le fichier txt station pour lire les stations dedans:
    std::ifstream flux(R"(..\stations.txt)");
    //on lit les stations dans le fichier. On sait qu'elles sont sous la forme "numéro:nom"
    if(flux){
        std::string ligne;
        int i=0;
        while(getline(flux, ligne)){
            std::string delimiter = ":";
            std::string name = ligne.substr(ligne.find(delimiter)+1, ligne.length());
            Station station(name, i);
            ligneA.push_back(station);
            i++;
        }
    }
    else{
        std::cout<<"erreur"<<std::endl;
    }

    //afficher toutes les stations récupérées:
    for(int i=0; i<ligneA.size(); i++){
        std::cout<<ligneA[i].number<<" "<<ligneA[i].name<<std::endl;
    }
    return 1;
}
