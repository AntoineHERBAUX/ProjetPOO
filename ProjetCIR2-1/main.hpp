#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "raylib.h"
#include "raymath.h"

const int MAX_PASSAGER=200;
const int MAX_VITESSE=80; //vitesse max en km/h
const int MIN_DISTANCE=100; //distance minimum entre deux rames en m
const int PASSAGERSCAPACITY=230; // le nombre maximum de passagers dans la rame
const int ACCELERATION=10;
const int DECELERATION=10;
const int CIRCULATING_RAME=15; // le nombre de rames en circulation
const bool TO_4CANTONS=true;
const bool TO_CHU=false;
const int monitor= GetCurrentMonitor();



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
    Vector2 Coordinates{}; // Coordonnées de la station

    void show_station() const; // affiche la station
    void add_passagers(int number); // ajoute des passagers à la station
    void remove_passagers(int number); // enlève des passagers à la station
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

    void show_rame() const; // affiche la rame
    void move_rame(std::vector<Station> ligneA); // fait avancer la rame
    void add_passagers(int number); // ajoute des passagers à la rame
    void remove_passagers(int number); // enlève des passagers à la rame
    void change_voie(); // change de voie

};

void test(); // fonction de test
void init_windows(); // initialise la fenêtre
void global_show(const std::vector<Station> ligneA,const std::vector<Rame> rames);
