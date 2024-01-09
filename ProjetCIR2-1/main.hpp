#include <iostream>
#include <iomanip>
#include <cstring>
#include <cerrno>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include <sstream>
#include "raylib.h"
#include "raymath.h"
#include <thread>
#include <chrono>
#include <algorithm>

const int SIMULATION_RATE = 20;// Vitesse de simulation : 1 = vitesse normale, pour observer le fonctionnement en accéléré, mieux vaut mettre 10 ou 20
const int MAX_VITESSE=80; //vitesse max en km/h
const int MAX_PASSAGER=100;
const int MIN_DISTANCE=100; //distance minimum entre deux rames en m
const int PASSAGERSCAPACITY=230; // le nombre maximum de passagers dans la rame
const int ACCELERATION=1;
const int DECELERATION=1;
const int CIRCULATING_RAME=16; // le nombre de rames en circulation
const bool TO_4CANTONS=true;
const bool TO_CHU=false;
const int monitor= GetCurrentMonitor();
const int MAX_PASSAGER_STATION=400;



class Rame;
class Station;

class Vector{
public:
    float x;
    float y;
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    void operator+=(const Vector& other);
    void operator-=(const Vector& other);
};

class Station{ // La classe Station permet de créer des objets Station avec différentes caractéritiques.
//Elles sont gérés par les fonctions de la classe Superviseur et de la classe Station
public :
    Station();
    Station(std::string name, int id);


    int number; // le numéro de la station
    std::string name; // Nom de la station
    int passagers; //nombre de passagers attendant dans la station
    int passagersCapacity; // le nombre maximum de passagers dans la station
    Vector Coordinates{}; // Coordonnées de la station

    void show_station() const; // affiche la station
    void new_passagers();
    void GetOut(int passagers);
    void GetIn(int passagers);
};


class Rame { // La classe Rame permet de créer des objets Rame avec différentes caractéritiques. Elles sont gérés par les fonctions de la classe Superviseur et de la classe Rame
public :
    Rame(bool sens, int id, std::vector<Station> ligneA);

    int number; // le numéro de la rame
    float vitesse; // la vitesse de la rame.
    int passagers; // le nombre de passagers dans la rame
    float distanceTraveled; // la distance parcourue sur la voie actuelle
    bool whichVoie; // si 0, on est dans l'aller (Lille->Villeneuve d'Asq), sinon on est dans le retour (Lille<-Villeneuve d'Asq)
    Vector Coordinates{}; // Coordonnées de la rame
    Station nextStation; // la station suivante
    int nextRameId; //quel est la prochaine rame
    bool EmergencyBrake; // si true, la rame est en arrêt d'urgence
    Image image; //l'image représentant la rame
    Texture2D texture; //la texture représentant la rame(c'est mieux car on peut éditer l'image en lui faisait des rotations)
    int degrees;

    void show_rame(); // affiche la rame
    void move_rame(std::vector<Station>& ligneA, std::vector<Rame>& rames); // fait avancer la rame
    void arretRame(std::vector<Station> ligneA);//arret de la rame
    void trade_passagers(); // fait monter et descendre les passagers
    Rame* NextRame(Rame rame, std::vector<Rame> rames, std::vector<Station> ligneA);


};
//superviseur

void emergency_break(Rame rame); // arrêt d'urgence
void skip_station(Rame rame); // saut de station
void choose_function(int function, Rame rame); // permet de choisir la fonction à appeler
int choose_rame(); // permet de choisir la rame à appeler



void test(); // fonction de test
void init_windows(); // initialise la fenêtre
void global_show(const std::vector<Station> ligneA,std::vector<Rame> rames, bool menu, Rame* target_rame); // affiche tout


float CalculateAngle(Vector point1, Vector point2); // calcule l'angle entre deux points

