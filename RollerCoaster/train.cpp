#include "train.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

train::train(u_char capacite, u_char tours) : eta(EtatTrain::UNLOAD), capa(capacite), nbTours(tours) {}

void train::rouler() {
    for (u_char i = 0; i < nbTours; i++) {
        load();
        run();
        unload();
    }
    cout << "\n[WaiFada Corporation] Fin de l'inauguration ! Le temps lui-même est confus." << endl;
}

void train::load() {
    cout << "\n[TRAIN DE LA HYPE] Le train approche du Portugal...." << endl;

    // ici le sleep fait en sorte que le train prend du retard pour que le voyageur prend la clé
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "[TRAIN DE LA HYPE] Le train arrive, il faut la clé du sas pour ouvrir !!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

    // Le train essaie de prendre la clé
    lock_guard<mutex> lock(mtx_sas);

    eta = EtatTrain::LOAD;
    cout << "[TRAIN DE LA HYPE] Portes ouvertes au PORTUGAL !! Embarquement immédiat !!!" << endl;

    attente_quai.release(capa);
    train_plein.acquire();
}

void train::run() {
    eta = EtatTrain::RUN;
    cout << "[TRAIN DE LA HYPE] VITESSE DÉFIANT LES LOIS DE LA LOGIQUE ATTEu_charE !" << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
}

void train::unload() {
    eta = EtatTrain::UNLOAD;
    cout << "[TRAIN DE LA HYPE] Retour au PORTUGAL. Tout le monde descend !" << endl;

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
