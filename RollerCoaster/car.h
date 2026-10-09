#ifndef CAR_H
#define CAR_H

#include <semaphore>

using namespace std;

class Car {
private:
    int C;
    counting_semaphore<500>& boardQueue;
    counting_semaphore<500>& unboardQueue;
    counting_semaphore<500>& allAboard;
    counting_semaphore<500>& allAshore;

public:
    Car(int capacite,
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
