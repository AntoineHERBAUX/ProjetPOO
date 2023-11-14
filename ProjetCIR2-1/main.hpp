#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

const int MAX_PASSAGER=200;
class Rame;
class Station;

class Station { // La classe Station permet de créer des objets Station avec différentes caractéritiques.
//Elles sont gérés par les fonctions de la classe Superviseur et de la classe Station
public :
    Station(std::string name, int id);

    int number; // le numéro de la station
    std::string name; // Nom de la station
    int passagers;
    int passagersCapacity; // le nombre maximum de passagers dans la station
    Rame *NextRame; // Quel est la rame qui arrive ?
};


class Rame { // La classe Rame permet de créer des objets Rame avec différentes caractéritiques. Elles sont gérés par les fonctions de la classe Superviseur et de la classe Rame
public :
    int number; // le numéro de la rame
    float maxVitesse; // Vitesse maximale de la rame
    float deccelerationRate; // le taux de decceleration (par exemple -1km/h par sec, soit 1). Ne peut on pas considérer qu'elle accélère aussi vite qu'elle décélère ?
    float accelerationRate; // le taux d'acceleration (par exemple 1km/h par sec, soit 1)
    float minDistanceBetweenRame; // la distance minimale autorisé entre deux rames, si elle est dépassé, on ralenti la rame derrière
    float vitesse; // la vitesse de la rame.
    bool isStopped; // Si vrai, des passagers peuvent monter dans la rame.
    int passagers; // le nombre de passagers dans la rame
    int passagersCapacity; // le nombre maximum de passagers dans la rame
    Rame* nextRame; // quel est la prochaine rame ? on met un pointeur car la prochaine rame ne fait pas partie de la classe Rame, mais on peut obtenier la prochaine rame via une rame, comme une liste chainée.
    Station* nextStation; // quel est la prochaine station ?
    float distanceNextRame; // la distance jusqu'a la prochaine rame, si elle est en dessous de la distance minimale autorisé on ralenti la rame
    float distanceNextStation; // la distance jusqu'a la prochaine station
    float distanceTraveled; // la distance parcourue sur la voie actuelle
    float percentageTraveled; // en fonction de la voie, la position de la rame sur la voie : 0% au début de la voie, 50% au milieu, 100% au bout,
    //ainsi si on est au bout, dès que c'est possible on change de voie
    bool whichVoie; // si 0, on est dans l'aller (Lille->Villeneuve d'Asq), sinon on est dans le retour (Lille<-Villeneuve d'Asq)
};

void test(); // fonction de test