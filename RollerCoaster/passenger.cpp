#include "passenger.h"
#include <iostream>

using namespace std;

Passenger::Passenger(int id, int capacite,
                     counting_semaphore<500>& ref_boardQueue,
                     counting_semaphore<500>& ref_unboardQueue,
                     counting_semaphore<500>& ref_allAboard,
                     counting_semaphore<500>& ref_allAshore,
                     mutex& ref_mut_boards,
                     mutex& ref_mut_unboards,
                     int& ref_boarders,
                     int& ref_unboarders)
    : id(id), C(capacite), boardQueue(ref_boardQueue), unboardQueue(ref_unboardQueue),
    allAboard(ref_allAboard), allAshore(ref_allAshore),
    mut_boards(ref_mut_boards), mut_unboards(ref_mut_unboards),
    boarders(ref_boarders), unboarders(ref_unboarders) {}

void Passenger::board() { cout << "[Passager " << id << "] monte dans la voiture." << endl; }
void Passenger::unboard() { cout << "[Passager " << id << "] descend de la voiture." << endl; }

void Passenger::faire_un_tour() {
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
