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
    this->EmergencyBrake = 0;
    this->image = LoadImage("./rame_big.png");
};


void Rame::move_rame(const std::vector<Station>& ligneA) {
    while(!WindowShouldClose()) {
        int x = this->nextStation.Coordinates.x - this->Coordinates.x;
        int y = this->nextStation.Coordinates.y - this->Coordinates.y;
        int degrees;
        if (x > 0 && y >= 0) {
            degrees = (atan(y / x)) * 57.29;
        }
        else if (x > 0 && y < 0) {
            degrees = (atan(y / x) + 6.28) * 57.29;
        }
        else if (x == 0 && y < 0) {
            degrees = 270;
        }
        else if (x == 0 && y > 0) {
            degrees = 90;
        }
        else if (x == 0 && y == 0) {
            degrees = this->degrees;
        }
        else {
            degrees = (atan(y / x) + 3.14) * 57.29;
        }

        if ((((this->degrees) - degrees) > 1) || (((this->degrees) - degrees) < -1)) {

            //UnloadImage(this->image);
            //Image image = LoadImage("./big_rame.png");
            //ImageRotate(&image, degrees);
            //(this->degrees) = degrees;
            //ImageResize(&image, 32, 32);
            //this->image = image;
        }



        if (this->Coordinates == this->nextStation.Coordinates) {
            trade_passagers();
            arretRame(ligneA);
        } else {
            //move(ligneA);
        }

        if (EmergencyBrake) {
            this->vitesse -= 2;
            return;
        }
        float getDistance = 6*sqrt((this->Coordinates.x - this->nextStation.Coordinates.x) *
                                 (this->Coordinates.x - this->nextStation.Coordinates.x) +
                                 (this->Coordinates.y - this->nextStation.Coordinates.y) *
                                 (this->Coordinates.y - this->nextStation.Coordinates.y));
        if (getDistance != 0) {
            this->Coordinates.x -=
                    (this->vitesse/(3.6*50/SIMULATION_RATE)) * ((this->Coordinates.x - this->nextStation.Coordinates.x) / getDistance);
            this->Coordinates.y -=
                    (this->vitesse/(3.6*50/SIMULATION_RATE)) * ((this->Coordinates.y - this->nextStation.Coordinates.y) / getDistance);
        }
        if (this->number == 1) {
            std::cout << "id : "  << this->number << ", x : " << std::setw(8) << this->Coordinates.x << ", y : " << std::setw(8) << this->Coordinates.y
                << ", vitesse :" << std::setw(8) << this->vitesse << ", go x : " << this->nextStation.Coordinates.x << ", go y : "
                << this->nextStation.Coordinates.y <<"    break distance" << std::setw(8) << ((((this->vitesse)) * (((this->vitesse) + 1))) / 14.4) << "m  distance : " << std::setw(8) << getDistance << "m   degrees:" << this->degrees  << std::endl;
        }
        if ((this->vitesse < MAX_VITESSE) && (((((this->vitesse)) * (((this->vitesse) + 1))) / 14.4) < getDistance)) {
            this->vitesse+=0.05 * SIMULATION_RATE;
        } else {
            if (getDistance < 1) {
                this->Coordinates.x -= (this->Coordinates.x - this->nextStation.Coordinates.x);
                this->Coordinates.y -= (this->Coordinates.y - this->nextStation.Coordinates.y);
                this->vitesse = 0;
            }
            if (this->vitesse > 0) {
                this->vitesse-=0.05 * SIMULATION_RATE;
            } else {
                arretRame(ligneA);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
/**
 * @brief Handles the stopping of a train at a station and updates its direction and next station.
 *
 * This method is designed to manage the train's (Rame) behavior when it stops at a station. It checks if the train's current coordinates match the coordinates of any station in the provided line (ligneA). If a match is found, and the station is indeed the train's next scheduled station, it then updates the train's direction and the next station it should head to. The train changes direction at the endpoints of the line.
 *
 * @param ligneA A vector of Station objects representing the stations along a train line.
 *
 * @note The function assumes that the train line is linear and that the train changes direction at the endpoints of the line.
 */
void Rame::arretRame(std::vector<Station> ligneA) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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


