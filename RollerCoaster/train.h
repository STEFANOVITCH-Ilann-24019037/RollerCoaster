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

    counting_semaphore<30> attente_quai{0};
    counting_semaphore<30> attente_descente{0};
    counting_semaphore<30> train_plein{0};
    counting_semaphore<30> train_vide{0};

    mutex mtx_compteurs;
    u_char boarders = 0;
    u_char unboarders = 0;

public:
    // mutex que le voyageur va bloquer
    mutex mtx_sas;

    train(u_char capacite, u_char nbTours);

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
