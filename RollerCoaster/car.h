#ifndef CAR_H
#define CAR_H

#include <semaphore>
#include <iostream>

using namespace std;

class Car {
private:
    unsigned int C;
    //ici on utilise <Max> car c demander dans le c++ 20 c la limite que peut atteindre le sémaphore
    counting_semaphore<500>& boardQueue;
    counting_semaphore<500>& unboardQueue;
    counting_semaphore<500>& allAboard;
    counting_semaphore<500>& allAshore;

public:
    //on recup les ref des sémaphore du main pour les lier au objet
    Car(unsigned int capacite,
        counting_semaphore<500>& ref_boardQueue,
        counting_semaphore<500>& ref_unboardQueue,
        counting_semaphore<500>& ref_allAboard,
        counting_semaphore<500>& ref_allAshore);

    void load();
    void run();
    void unload();

    void lancer_tour();
};

#endif // CAR_H
