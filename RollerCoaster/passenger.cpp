#include "passenger.h"
#include "car.h"
#include <iostream>

using namespace std;

passenger::passenger(string n) : nom(n), etat(EtatPassager::Unboard) {}

void passenger::board() {
    etat = EtatPassager::Board;
    cout << "[BOARD] " << nom << " monte." << endl;
}

void passenger::unboard() {
    etat = EtatPassager::Unboard;
    cout << "[UNBOARD] " << nom << " descend." << endl;
}

void passenger::vivre(car& voiture) {
    voiture.arriver(this);
}