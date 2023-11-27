#include "main.hpp"

Rame::Rame(bool sens, int id,std::vector<Station> ligneA){
    this->number = id;
    this->whichVoie=sens;
    if(sens==0) this->Coordinates={ligneA[0].Coordinates};
    else this->Coordinates={ligneA[ligneA.size()-1].Coordinates};
    this->vitesse=0;
    this->passagers=0;
    this->distanceTraveled=0;
};

void Rame::add_passagers_from(Station* station) {
    while(this->passagers<PASSAGERSCAPACITY && station->passagers>0){
        this->passagers++;
        station->passagers--;
    }
}

void Rame::remove_passagers_to(Station* station) {
    while(this->passagers>0 && station->passagers<station->passagersCapacity){
        this->passagers--;
        station->passagers++;
    }
}

void Rame::move_rame(const std::vector<Station>& ligneA) {
    if(this->whichVoie==TO_CHU){
        if(this->distanceTraveled<200){
            this->distanceTraveled+=this->vitesse/3600;
            this->Coordinates.x+=this->vitesse/3600;
        }
        else{
            this->distanceTraveled=0;
            this->whichVoie=TO_4CANTONS;
        }
    }
    else{
        if(this->distanceTraveled<200){
            this->distanceTraveled+=this->vitesse/3600;
            this->Coordinates.x-=this->vitesse/3600;
        }
        else{
            this->distanceTraveled=0;
            this->whichVoie=0;
        }
    }
}