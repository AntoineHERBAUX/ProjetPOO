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
    this->EmergencyBrake = false;
    this->image = LoadImage("./rame_big.png");
};

float CalculateAngle(Vector point1, Vector point2){
    float dx = point2.x - point1.x;
    float dy = point2.y - point1.y;

    return atan2f(dy, dx) * RAD2DEG;
}

void Rame::move_rame(std::vector<Station>& ligneA) {
    while(!WindowShouldClose()) {
        int x = this->nextStation.Coordinates.x - this->Coordinates.x;
        int y = this->nextStation.Coordinates.y - this->Coordinates.y;
        float degrees;

        if (this->Coordinates == this->nextStation.Coordinates) {
            trade_passagers();
            arretRame(ligneA);
        }

        if (this->EmergencyBrake && this->vitesse > 0) {
            this->vitesse -= 2;
        }
        else {
            float getDistance = 6 * sqrt((this->Coordinates.x - this->nextStation.Coordinates.x) *
                                         (this->Coordinates.x - this->nextStation.Coordinates.x) +
                                         (this->Coordinates.y - this->nextStation.Coordinates.y) *
                                         (this->Coordinates.y - this->nextStation.Coordinates.y));
            if (getDistance != 0) {
                this->Coordinates.x -=
                        (this->vitesse / (3.6 * 50 / SIMULATION_RATE)) *
                        ((this->Coordinates.x - this->nextStation.Coordinates.x) / getDistance);
                this->Coordinates.y -=
                        (this->vitesse / (3.6 * 50 / SIMULATION_RATE)) *
                        ((this->Coordinates.y - this->nextStation.Coordinates.y) / getDistance);
            }

            float distance_with_next_rame = 0;
            if (this->nextRameId < size(ligneA)) {
                distance_with_next_rame = sqrt((this->Coordinates.x - ligneA[this->nextRameId].Coordinates.x) *
                                               (this->Coordinates.x - ligneA[this->nextRameId].Coordinates.x) +
                                               (this->Coordinates.y - ligneA[this->nextRameId].Coordinates.y) *
                                               (this->Coordinates.y - ligneA[this->nextRameId].Coordinates.y));
            }

            int distance_darret=0;
            if(this->vitesse>0) distance_darret=(this->vitesse)*(this->vitesse)/(0.5*SIMULATION_RATE);

            if ((this->vitesse < MAX_VITESSE) &&
                (((((this->vitesse)) * (((this->vitesse) + 1))) / 14.4) < getDistance)) {
                this->vitesse += 0.5 * SIMULATION_RATE;
            } else {
                if (getDistance < 1) {
                    this->Coordinates.x -= (this->Coordinates.x - this->nextStation.Coordinates.x);
                    this->Coordinates.y -= (this->Coordinates.y - this->nextStation.Coordinates.y);
                    this->vitesse = 0;
                }
                if (this->vitesse > 0) {
                    this->vitesse -= 0.05 * SIMULATION_RATE;
                } else {
                    trade_passagers();
                    if(nextStation.number==0 && whichVoie==TO_4CANTONS|| nextStation.number==ligneA.size()-1 && whichVoie==TO_CHU){
                        nextStation.passagers+=passagers;
                        passagers=0;
                    }
                    if(nextStation.number==0 && whichVoie==TO_CHU|| nextStation.number==ligneA.size()-1 && whichVoie==TO_4CANTONS){
                        passagers+=nextStation.passagers;
                        nextStation.passagers=0;
                    }
                    arretRame(ligneA);
                }
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
                    this->nextStation = ligneA[i + 1];
                    
                }
                else {
                    this->nextStation = ligneA[i - 1];
    
                }
        }
    }
}




void Rame::trade_passagers() {
    int passagers_going_out = 0;
    int passagers_going_in = 0;
    passagers_going_out=rand()%(passagers+1);
    passagers_going_out=std::min(passagers_going_out,MAX_PASSAGER_STATION-nextStation.passagers);
    nextStation.passagers+=passagers_going_out;
    passagers-=passagers_going_out;
    passagers_going_in=std::min(MAX_PASSAGER, int(nextStation.passagers/2));
    nextStation.passagers-=passagers_going_in;
    passagers+=passagers_going_in;
}


