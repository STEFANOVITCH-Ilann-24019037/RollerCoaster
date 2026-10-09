#ifndef PASSENGER_H
#define PASSENGER_H

#include <semaphore>
#include <mutex>

using namespace std;

class Passenger {
private:
    int id;
    int C;
    counting_semaphore<500>& boardQueue;
    counting_semaphore<500>& unboardQueue;
    counting_semaphore<500>& allAboard;
    counting_semaphore<500>& allAshore;
    mutex& mut_boards;
    mutex& mut_unboards;


    int& boarders;
    int& unboarders;

public:
    Passenger(int id, int capacite,
              counting_semaphore<500>& ref_boardQueue,
              counting_semaphore<500>& ref_unboardQueue,
              counting_semaphore<500>& ref_allAboard,
              counting_semaphore<500>& ref_allAshore,
              mutex& ref_mut_boards,
              mutex& ref_mut_unboards,
              int& ref_boarders,
              int& ref_unboarders);

    void board();
    void unboard();
    void faire_un_tour();
};

#endif // PASSENGER_H
