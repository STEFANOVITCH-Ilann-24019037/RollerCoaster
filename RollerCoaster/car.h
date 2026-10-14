#ifndef CAR_H
#define CAR_H

#include <vector>
#include <mutex>
#include <condition_variable>
#include "passenger.h"

using namespace std;

enum class EtatCar {
    LOAD,
    RUN,
    UNLOAD
};

class car {
private:
    EtatCar eta;
    int capa;
    int nbTours;
    vector<passenger*> passengers;
    vector<passenger*> fileDAttente;
    mutex mtx;
    condition_variable cv;

public:
    car(int capacite, int nbTours);

    void rouler();
    void load();
    void run();
    void unload();

    void arriver(passenger* p);
};

#endif