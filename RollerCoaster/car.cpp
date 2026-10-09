#include "car.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Car::Car(int capacite,
         counting_semaphore<500>& ref_boardQueue,
         counting_semaphore<500>& ref_unboardQueue,
         counting_semaphore<500>& ref_allAboard,
         counting_semaphore<500>& ref_allAshore)
    : C(capacite), boardQueue(ref_boardQueue), unboardQueue(ref_unboardQueue),
    allAboard(ref_allAboard), allAshore(ref_allAshore) {}

void Car::load() { cout << "[Voiture] Ouverture des portes pour l'embarquement" << endl; }
void Car::run() {
    cout << "[Voiture] Le manege tourne.............." << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
}
void Car::unload() { cout << "[Voiture] Tout le monde descend c'est terminer" << endl; }

void Car::lancer_tour() {
    for(int i = 0; i < 3; ++i) {
        load();
        boardQueue.release(C);

        allAboard.acquire();

        run();

        unload();
        unboardQueue.release(C);

        allAshore.acquire();
    }
}
