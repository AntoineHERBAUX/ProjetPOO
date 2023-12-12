//
// Created by Admin on 12/12/2023.
//


#include "main.hpp"

void choose_function(int function,Rame rame){
    switch(function){
        case 1: //emergency break
            emergency_break(rame);
            break;
        case 2: //skip station
            skip_station(rame);
            break;
        default:
            std::cout<<"Erreur, fonction non reconnue"<<std::endl;
            break;
    }

}



void emergency_break(Rame rame){
    rame.EmergencyBrake=true;
}

void skip_station(Rame rame){
    std::cout<<"Rame:"<<std::endl;
}