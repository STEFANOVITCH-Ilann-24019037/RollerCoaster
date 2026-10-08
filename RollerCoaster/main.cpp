#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>
#include <vector>
#include "car.h"
#include "passenger.h"

using namespace std;

mutex mut_boards;
mutex mut_unboards;

int main()
{

    counting_semaphore<500> boardQueue (0);
    counting_semaphore<500> unboardQueue (0);
    counting_semaphore<500> allAboard (0);
    counting_semaphore<500> allAshore (0);

    int boards = 0;
    int unboards = 0;

    Car voiture(4,boardQueue,unboardQueue,allAboard,allAshore );

    thread T_voiture(&Car::lancer_tour, &voiture);

    vector<thread> mes_passagers;
    int nb_passagers = 10;

    vector<passager>liste_passagers;

    for(int j=0; j < nb_passagers; ++j)
        mes_passagers.push_back(thread(&Passagers::faire_un_toure, &liste_passagers[j]));
    for (thread & th : mes_passagers) th.join();



    cout << "Hello World!" << endl;

    T_voiture.join();

    return 0;
}
