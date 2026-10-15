#include "train.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

train::train(int capacite, int tours) : eta(EtatTrain::UNLOAD), capa(capacite), nbTours(tours) {}

void train::rouler() {
    for (int i = 0; i < nbTours; i++) {
        load();
        run();
        unload();
    }
    cout << "\n[WaiFada Corporation] Fin de l'inauguration ! Le temps lui-même est confus." << endl;
}

void train::load() {
    eta = EtatTrain::LOAD;
    cout << "\n[TRAIN DE LA HYPE] Portes ouvertes au PORTUGAL ! Embarquement immédiat !" << endl;

    // le train laisse les gens monter
    attente_quai.release(capa);
    // le train reste a l'arret jusqu'a se que le dernier passager signal que c'est plein
    train_plein.acquire();
}

void train::run() {
    eta = EtatTrain::RUN;
    cout << "[TRAIN DE LA HYPE] VITESSE DÉFIANT LES LOIS DE LA LOGIQUE ATTEINTE ! TOUR DE L'EUROPE EN COURS !!!" << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
}

void train::unload() {
    eta = EtatTrain::UNLOAD;
    cout << "[TRAIN DE LA HYPE] Retour au PORTUGAL en moins d'une heure. Tout le monde descend !" << endl;

    attente_descente.release(capa);
    train_vide.acquire();
}


void train::attendre_ouverture() {
    attente_quai.acquire();
}

void train::passager_monte() {
    lock_guard<mutex> lock(mtx_compteurs);
    boarders++;
    if (boarders == capa) {
        train_plein.release();
        boarders = 0;
    }
}

void train::attendre_fin_tour() {
    attente_descente.acquire();
}

void train::passager_descendu() {
    lock_guard<mutex> lock(mtx_compteurs);
    unboarders++;
    if (unboarders == capa) {
        train_vide.release();
        unboarders = 0;
    }
}
