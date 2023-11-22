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



