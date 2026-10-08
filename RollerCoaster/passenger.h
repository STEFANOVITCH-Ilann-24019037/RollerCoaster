#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

using namespace std;

class car;

enum class EtatPassager {
    Board,
    Unboard
};

class passenger {
public:
    string nom;
    EtatPassager etat;

    passenger(string n);

    void board();
    void unboard();
    void vivre(car& voiture);
};

#endif