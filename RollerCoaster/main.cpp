#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include "train.h"
#include "voyageur.h"

using namespace std;

int main() {
    cout << "          TRAIN DE LA HYYYYYYYYYYYYYPE EN AVANT !!        " << endl;


    const u_char CAPACITE = 3;
    const u_char NB_TOURS = 2;
    const u_char NB_VOYAGEURS = CAPACITE * NB_TOURS;

    train le_train(CAPACITE, NB_TOURS);

    vector<voyageur> voyageurs;
    voyageurs.reserve(NB_VOYAGEURS);

    for (u_char i = 0; i < NB_VOYAGEURS; i++) {
        voyageurs.emplace_back("voyageur" + to_string(i + 1));
    }

    vector<thread> threads;


    // on lance les threads des voyageurs
    for (auto& v : voyageurs) {
        threads.emplace_back(&voyageur::vivre, &v, ref(le_train));
    }
    // on lance le thread du train
    threads.emplace_back(&train::rouler, &le_train);


    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
