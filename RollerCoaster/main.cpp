#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <deque>
#include "train.h"
#include "voyageur.h"

using namespace std;

int main() {
    cout << "          TRAIN DE LA HYYYYYYYYYYYYYPE EN AVANT !!        " << endl;


    const u_char CAPACITE = 3;
    const u_char NB_TOURS = 2;
    const u_char NB_TRAINS = 2 ;
    const u_char NB_VOYAGEURS = CAPACITE * NB_TOURS*NB_TRAINS;



    vector<voyageur> voyageurs;
    deque<train> trains ;

    voyageurs.reserve(NB_VOYAGEURS);

    for (u_char i = 0; i < NB_TRAINS; ++i) {
        trains.emplace_back(CAPACITE, NB_TOURS, "train " + to_string(i + 1));
    }

    for (u_char i = 0; i < NB_VOYAGEURS; ++i) {
        voyageurs.emplace_back("voyageur " + to_string(i + 1));
    }

    vector<thread> threads;

    // Lancement du thread du train
    for (auto& t : trains)
    {
        threads.emplace_back(&train::rouler, &t);
    }

    // Lancement des threads des voyageurs
    for (u_char i = 0; i < NB_VOYAGEURS; ++i) {
        threads.emplace_back(&voyageur::vivre, &voyageurs[i], ref(trains[i % NB_TRAINS]));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
