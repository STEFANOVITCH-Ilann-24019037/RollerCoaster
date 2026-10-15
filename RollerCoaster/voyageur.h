#ifndef VOYAGEUR_H
#define VOYAGEUR_H

#include <string>

using namespace std;

class train;

enum class EtatVoyageur {
    Board,
    Unboard
};

class voyageur {
public:
    string nom;
    EtatVoyageur etat;

    voyageur(string n);

    void board();
    void unboard();
    void vivre(train& le_train);
};

#endif
