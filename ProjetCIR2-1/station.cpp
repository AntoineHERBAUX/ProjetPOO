#include <utility>

#include "main.hpp"
/**
 *  @brief intialise une station
 *  @param name nom de la station
 *  @param id numéro de la station
 *  @return La station initialisée
 */
Station::Station(std::string name, int id,std::vector<Station> ligneA){
    this->number = id;
    this->name=std::move(name);
    this->passagers=0;
    this->passagersCapacity=PASSAGERSCAPACITY;
    this->Coordinates={0,0};
}

void Station::new_passagers(){
    int new_passagers=0;
    if(rand()%20*TIME_CONVERTER==1) new_passagers+=rand()%10;
    passagers+=new_passagers;
}

void Rame::trade_passagers() {
    int passagers_going_out = 0;
    int passagers_going_in = 0;
    if(Coordinates!=nextStation->Coordinates) return;
    passagers_going_out=rand()%(passagers+1);
    passagers_going_out=std::min(passagers_going_out,nextStation->passagers);
    nextStation->passagers+=passagers_going_out;
    passagers-=passagers_going_out;
    passagers_going_in=rand()%(nextStation->passagersCapacity-nextStation->passagers);
    passagers_going_in=std::min(passagers_going_in,MAX_PASSAGER-passagers);
    nextStation->passagers-=passagers_going_in;
    passagers+=passagers_going_in;
}




