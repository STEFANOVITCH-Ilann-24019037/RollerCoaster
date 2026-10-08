#include "car.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

car::car(int capacite, int nbTours) : eta(EtatCar::UNLOAD), capa(capacite), nbTours(nbTours) {}

void car::rouler() {
    for (int i = 0; i < nbTours; i++) {
        load();
        run();
        unload();
    }
}

void car::arriver(passenger* p) {
    lock_guard<mutex> lock(mtx);
    fileDAttente.push_back(p);
    cout << "[FILE] " << p->nom << " fait la queue." << endl;
    cv.notify_one();
}

void car::load() {
    unique_lock<mutex> lock(mtx);
    eta = EtatCar::LOAD;
    cout << "[LOAD] Chargement..." << endl;

    while ((int)passengers.size() < capa) {
        while (fileDAttente.empty()) {
            cv.wait(lock);
        }
        passenger* p = fileDAttente.front();
        fileDAttente.erase(fileDAttente.begin());
        p->board();
        passengers.push_back(p);
    }
}

void car::run() {
    {
        lock_guard<mutex> lock(mtx);
        eta = EtatCar::RUN;
        cout << "[RUN] La voiture est pleine, depart." << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(5000));
}

void car::unload() {
    lock_guard<mutex> lock(mtx);
    eta = EtatCar::UNLOAD;
    cout << "[UNLOAD] Dechargement..." << endl;

    for (passenger* p : passengers) {
        p->unboard();
    }
    passengers.clear();
}