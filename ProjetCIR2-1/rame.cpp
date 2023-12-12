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
                    std::cout << "i : " << i << "name : " << ligneA[i + 1].name << "x : " << ligneA[i + 1].Coordinates.x << std::endl;
                    this->nextStation = ligneA[i + 1];//probleme aled
                    
                }
                else {
                    std::cout << "i : " << i << "name : " << ligneA[i - 1].name << "x : " << ligneA[i - 1].Coordinates.x << std::endl;
                    this->nextStation = ligneA[i - 1];
    
                }
        }
    }
}



//
//void Rame::move_rame(const std::vector<Station>& ligneA) {
//    if(this->whichVoie==TO_CHU){
//        if(this->distanceTraveled<200){
//            this->distanceTraveled+=this->vitesse/3600;
//            this->Coordinates.x+=this->vitesse/3600;
//        }
//        else{
//            this->distanceTraveled=0;
//            this->whichVoie=TO_4CANTONS;
//        }
//    }
//    else{
//        if(this->distanceTraveled<200){
//            this->distanceTraveled+=this->vitesse/3600;
//            this->Coordinates.x-=this->vitesse/3600;
//        }
//        else{
//            this->distanceTraveled=0;
//            this->whichVoie=0;
//        }
//    }
//}