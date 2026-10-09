#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>
#include <vector>
#include "car.h"
#include "passenger.h"

using namespace std;

int main() {
    int C = 4;
    int nb_passagers = 12;

    counting_semaphore<500> boardQueue(0);
    counting_semaphore<500> unboardQueue(0);
    counting_semaphore<500> allAboard(0);
    counting_semaphore<500> allAshore(0);

    mutex mut_boards;
    mutex mut_unboards;

    // les mutex du deadlock
    mutex mut_billet;
    mutex mut_portillon;

    int boarders = 0;
    int unboarders = 0;

    Car voiture(C, boardQueue, unboardQueue, allAboard, allAshore);
    thread T_voiture(&Car::lancer_tour, &voiture);

    vector<Passenger> liste_passagers;
    liste_passagers.reserve(nb_passagers);

    for(int j = 0; j < nb_passagers; ++j) {
        liste_passagers.emplace_back(j, C, boardQueue, unboardQueue, allAboard, allAshore,
                                     mut_boards, mut_unboards,
                                     mut_billet, mut_portillon,
                                     boarders, unboarders);
    }

    vector<thread> mes_passagers;
    for(int j = 0; j < nb_passagers; ++j) {
        mes_passagers.push_back(thread(&Passenger::faire_un_tour, &liste_passagers[j]));
    }

    for (thread& th : mes_passagers) {
        th.join();
    }
    T_voiture.join();

    cout << "Fin de la journee." << endl;
    return 0;
}
