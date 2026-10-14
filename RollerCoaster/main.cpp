#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include "car.h"
#include "passenger.h"

using namespace std;

int main() {
    const int CAPACITE = 3;
    const int NB_TOURS = 2;

    car voiture(CAPACITE, NB_TOURS);

    vector<passenger> passagers;
    for (int i = 0; i < CAPACITE * NB_TOURS; i++) {
        passagers.emplace_back("P" + to_string(i + 1));
    }

    vector<thread> threads;
    threads.emplace_back(&car::rouler, &voiture);
    for (auto& p : passagers) {
        threads.emplace_back(&passenger::vivre, &p, ref(voiture));
    }

    for (auto& t : threads) {
        t.join();
    }

    cout << "Fin." << endl;
    return 0;
}