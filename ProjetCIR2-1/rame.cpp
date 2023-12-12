#include "main.hpp"

Rame::Rame(bool sens, int id,std::vector<Station> ligneA){
    this->number = id;
    this->whichVoie=sens;
    if(sens==0) this->Coordinates={ligneA[0].Coordinates};
    else this->Coordinates={ligneA[ligneA.size()-1].Coordinates};
    this->vitesse=0;
    this->passagers=0;
    this->distanceTraveled=0;
    this->nextRameId = id + 1;
    this->nextStation = Station("null", 0);
};


void Rame::move_rame(const std::vector<Station>& ligneA) {
    if (EmergencyBrake) {
        this->vitesse -=2;
        return;
    }
    float getDistance = sqrt((this->Coordinates.x - this->nextStation.Coordinates.x) * (this->Coordinates.x - this->nextStation.Coordinates.x) + (this->Coordinates.y - this->nextStation.Coordinates.y) * (this->Coordinates.y - this->nextStation.Coordinates.y));
    if (getDistance != 0) {
        this->Coordinates.x -= (this->vitesse / 36) * ((this->Coordinates.x - this->nextStation.Coordinates.x) / getDistance);
        this->Coordinates.y -= (this->vitesse / 36) * ((this->Coordinates.y - this->nextStation.Coordinates.y) / getDistance);
    }
    std::cout << "id : " << this->number << ", x : " << this->Coordinates.x << ", y : " << this->Coordinates.y << ", vitesse :" << this->vitesse << ", go x : " << this->nextStation.Coordinates.x << ", go y : " << this->nextStation.Coordinates.y << std::endl;
    if((this->vitesse<MAX_VITESSE)&&((((this->vitesse)*((this->vitesse+1)))/2) < getDistance*18)){
        this->vitesse++;
    }
    else {
        if (getDistance < 1) {
            this->Coordinates.x -= (this->Coordinates.x - this->nextStation.Coordinates.x);
            this->Coordinates.y -= (this->Coordinates.y - this->nextStation.Coordinates.y);
        }
        if (this->vitesse > 0) {
            this->vitesse--;
        }
        else {
            arretRame(ligneA);
        }
    }
}

void Rame::arretRame(std::vector<Station> ligneA) {
    for (int i = 0; i < size(ligneA); i++) {
        if ((this->Coordinates==(ligneA[i]).Coordinates)&&(ligneA[i].number)==this->nextStation.number) {
            if (i == 0 && this->whichVoie == 1) {
                this->whichVoie = 0;
            }
            if ((i == size(ligneA) - 1) && (this->whichVoie == 0)) {
                this->whichVoie = 1;
            };
                if (this->whichVoie == 0) {
                    //std::cout << "i : " << i << "name : " << ligneA[i + 1].name << "x : " << ligneA[i + 1].Coordinates.x << std::endl;
                    this->nextStation = ligneA[i + 1];
                    
                }
                else {
                    //std::cout << "i : " << i << "name : " << ligneA[i - 1].name << "x : " << ligneA[i - 1].Coordinates.x << std::endl;
                    this->nextStation = ligneA[i - 1];
    
                }
        }
    }
}




void Rame::trade_passagers() {
    int passagers_going_out = 0;
    int passagers_going_in = 0;
    if(Coordinates!=nextStation.Coordinates) return;
    passagers_going_out=rand()%(passagers+1);
    passagers_going_out=std::min(passagers_going_out,nextStation.passagers);
    nextStation.passagers+=passagers_going_out;
    passagers-=passagers_going_out;
    passagers_going_in=rand()%(nextStation.passagersCapacity-nextStation.passagers);
    passagers_going_in=std::min(passagers_going_in,MAX_PASSAGER-passagers);
    nextStation.passagers-=passagers_going_in;
    passagers+=passagers_going_in;
}