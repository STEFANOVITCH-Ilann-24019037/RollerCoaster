#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <mutex>
#include <semaphore>
#include "voyageur.h"

using namespace std;

enum class EtatTrain {
    LOAD,
    RUN,
    UNLOAD
};

class train {
private:
    EtatTrain eta;
    u_char capa;
    u_char nbTours;
    string nom;

    //ici on utilise la template de c++20 qui gère les condition
    counting_semaphore<500> attente_quai{0};
    counting_semaphore<500> attente_descente{0};
    counting_semaphore<500> train_plein{0};
    counting_semaphore<500> train_vide{0};

    // combien de personnes sont montées ou descendues
    mutex mtx_compteurs;
    int boarders = 0;
    int unboarders = 0;

public:
    train(u_char capacite, u_char nbTours,string nom);

    void rouler();
    void load();
    void run();
    void unload();


    void attendre_ouverture();
    void passager_monte();
    void attendre_fin_tour();
    void passager_descendu();
};

#endif
