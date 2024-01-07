#include <utility>

#include "main.hpp"
/**
 *  @brief intialise une station
 *  @param name nom de la station
 *  @param id numéro de la station
 *  @return La station initialisée
 */
Station::Station() {
    this->number = 0;
    this->name = std::move("null");
    
    this->passagersCapacity = MAX_PASSAGER_STATION;
    this->passagers = rand() % passagersCapacity;
    this->Coordinates = { 0,0 };
}


Station::Station(std::string name="null", int id=0) {
    this->number = id;
    this->name=std::move(name);
    this->passagers= rand() % passagersCapacity;
    this->passagersCapacity= MAX_PASSAGER_STATION;
    this->Coordinates={0,0};
}

void Station::new_passagers(){
    int new_passagers=0;
    new_passagers= rand() % (passagersCapacity/20 - passagers);
    passagers+=new_passagers;
}

void Station::GetOut(int passagers) {
    this->passagers -= passagers;
}

void Station::GetIn(int passagers) {
    this->passagers += passagers;
}

