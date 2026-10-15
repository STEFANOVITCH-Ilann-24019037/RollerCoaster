#include "voyageur.h"
#include "train.h"
#include <iostream>

using namespace std;

voyageur::voyageur(string n) : nom(n), etat(EtatVoyageur::Unboard) {}

void voyageur::board() {
    etat = EtatVoyageur::Board;
    cout << "[VOYAGEUR] " << nom << " a payé 99999 centimes et monte." << endl;
}

void voyageur::unboard() {
    etat = EtatVoyageur::Unboard;
    cout << "[VOYAGEUR] " << nom << " a survécu à l'expérience et descend." << endl;
}

void voyageur::vivre(train& le_train) {
        {

        // le passager garde la clé
        lock_guard<mutex> lock(le_train.mtx_sas);

        cout << "[" << nom << "] prend la clé du sas et s'endort sur le quai..." << endl;


        // en attendant il garde toujour la clé
        le_train.attendre_ouverture();

        this->board();
        le_train.passager_monte();
    }

    le_train.attendre_fin_tour();

    this->unboard();
    le_train.passager_descendu();
}
