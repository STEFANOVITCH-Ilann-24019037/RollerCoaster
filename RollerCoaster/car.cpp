#include "car.h"

using namespace std;

Car::Car(unsigned int capacite,
         counting_semaphore<500>& ref_boardQueue,
         counting_semaphore<500>& ref_unboardQueue,
         counting_semaphore<500>& ref_allAboard,
         counting_semaphore<500>& ref_allAshore)
    : C(capacite), boardQueue(ref_boardQueue), unboardQueue(ref_unboardQueue), allAboard(ref_allAboard), allAshore(ref_allAshore)
{
}

void Car::load(){
    cout << "Ouverture des portes pour l'embarquement" << endl;
}

void Car::run(){
    cout << "Sa tourne...." << endl;
}

void Car::unload(){
    cout << "Fin du tour, ouverture pour descendre" << endl;
}

void Car::lancer_tour(){
    boardQueue.realise(C);
}

