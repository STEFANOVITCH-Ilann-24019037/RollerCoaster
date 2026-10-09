#include "passenger.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Constructeur mis à jour
Passenger::Passenger(int id, int capacite,
                     counting_semaphore<500>& ref_boardQueue,
                     counting_semaphore<500>& ref_unboardQueue,
                     counting_semaphore<500>& ref_allAboard,
                     counting_semaphore<500>& ref_allAshore,
                     mutex& ref_mut_boards,
                     mutex& ref_mut_unboards,
                     mutex& ref_mut_billet,
                     mutex& ref_mut_portillon,
                     int& ref_boarders,
                     int& ref_unboarders)
    : id(id), C(capacite), boardQueue(ref_boardQueue), unboardQueue(ref_unboardQueue),
    allAboard(ref_allAboard), allAshore(ref_allAshore),
    mut_boards(ref_mut_boards), mut_unboards(ref_mut_unboards),
    mut_billet(ref_mut_billet), mut_portillon(ref_mut_portillon),
    boarders(ref_boarders), unboarders(ref_unboarders) {}

void Passenger::board() {
    cout << "[Passager " << id << "] monte dans la voiture." << endl;
}
void Passenger::unboard() {
    cout << "[Passager " << id << "] descend de la voiture." << endl;
}

void Passenger::faire_un_tour() {

    if (id % 2 == 0) {
        // Les passagers pairs prennent le Billet (A) puis le Portillon (B)
        lock_guard<mutex> lockA(mut_billet);
        cout << "Passager " << id << " a valide son billet. Attente du portillon..." << endl;
        this_thread::sleep_for(chrono::milliseconds(50));

        lock_guard<mutex> lockB(mut_portillon);
        cout << "Passager " << id << " a passe le portillon." << endl;


    } else {
        // Les passagers impairs prennent le Portillon (B) puis le Billet (A)
        lock_guard<mutex> lockB(mut_portillon);
        cout << "Passager " << id << " a passe le portillon. Attente de validation du billet..." << endl;

        this_thread::sleep_for(chrono::milliseconds(50));

        lock_guard<mutex> lockA(mut_billet);
        cout << "Passager " << id << " a valide son billet." << endl;
    }

    boardQueue.acquire();
    board();

    {
        lock_guard<mutex> lock(mut_boards);
        boarders += 1;
        if (boarders == C) {
            allAboard.release();
            boarders = 0;
        }
    }

    unboardQueue.acquire();
    unboard();

    {
        lock_guard<mutex> lock(mut_unboards);
        unboarders += 1;
        if (unboarders == C) {
            allAshore.release();
            unboarders = 0;
        }
    }
}
