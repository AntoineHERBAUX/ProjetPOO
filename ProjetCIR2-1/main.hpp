#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "raylib.h"

const int MAX_PASSAGER=200;
const int MAX_VITESSE=80; //vitesse max en km/h
const int MIN_DISTANCE=100; //distance minimum entre deux rames en m
const int PASSAGERSCAPACITY=230; // le nombre maximum de passagers dans la rame
const int ACCELERATION=10;
const int DECELERATION=10;
const int CIRCULATING_RAME=30; // le nombre de rames en circulation
const bool TO_4CANTONS=true;
const bool TO_CHU=false;


class Rame;
class Station;



class Station { // La classe Station permet de créer des objets Station avec différentes caractéritiques.
//Elles sont gérés par les fonctions de la classe Superviseur et de la classe Station
public :

    Station(std::string name, int id, std::vector<Station> ligneA);

    int number; // le numéro de la station
    std::string name; // Nom de la station
    int passagers;
    int passagersCapacity; // le nombre maximum de passagers dans la station
    Rame *presentRame{}; // QUelle rame est à quai ? nullptr si aucune
    Vector2 Coordinates{}; // Coordonnées de la station
};


class Rame { // La classe Rame permet de créer des objets Rame avec différentes caractéritiques. Elles sont gérés par les fonctions de la classe Superviseur et de la classe Rame
public :
    Rame(bool sens, int id, std::vector<Station> ligneA);

    int number; // le numéro de la rame
    float vitesse; // la vitesse de la rame.
    int passagers; // le nombre de passagers dans la rame
    float distanceTraveled; // la distance parcourue sur la voie actuelle
    bool whichVoie; // si 0, on est dans l'aller (Lille->Villeneuve d'Asq), sinon on est dans le retour (Lille<-Villeneuve d'Asq)
    Vector2 Coordinates{}; // Coordonnées de la rame
};

void test(); // fonction de test