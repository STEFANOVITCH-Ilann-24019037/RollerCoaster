#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include "train.h"
#include "voyageur.h"

using namespace std;

int main() {
    cout << "          TRAIN DE LA HYYYYYYYYYYYYYPE EN AVANT !!        " << endl;


    const int CAPACITE = 3;
    const int NB_TOURS = 2;
    const int NB_VOYAGEURS = CAPACITE * NB_TOURS;

    train le_train(CAPACITE, NB_TOURS);

    vector<voyageur> voyageurs;
    voyageurs.reserve(NB_VOYAGEURS);

    for (int i = 0; i < NB_VOYAGEURS; i++) {
        voyageurs.emplace_back("voyageur " + to_string(i + 1));
    }

    vector<thread> threads;

    // Lancement du thread du train
    threads.emplace_back(&train::rouler, &le_train);

    // Lancement des threads des voyageurs
    for (auto& v : voyageurs) {
        threads.emplace_back(&voyageur::vivre, &v, ref(le_train));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
