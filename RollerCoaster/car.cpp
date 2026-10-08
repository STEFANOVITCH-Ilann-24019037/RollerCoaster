#include <iostream>
#include <vector>
#include <string>

// Énumération pour l'état (eta)
enum class Etat {
    LOAD,
    RUN,
    UNLOAD
};

class Car {
private:
    Etat eta;
    int capa;
    std::vector<passenger> passengers;

public:
    Car(int capacite) : eta(Etat::LOAD), capa(capacite) {}

    void load(std::vector<passenger>& fileDAttente) {
        eta = Etat::LOAD;

        while (passengers.size() < capa && !fileDAttente.empty()) {
            passengers.push_back(fileDAttente.front());
            fileDAttente.erase(fileDAttente.begin());
        }
    }

    void run() {
        if (passengers.size() == capa) {
            eta = Etat::RUN;
            std::cout << "[RUN] La voiture est pleine, départ." << std::endl;
        } else {
            std::cout << "[ERREUR] La voiture n'est pas pleine, impossible de lancer le RUN." << std::endl;
        }
    }

    void unload(std::vector<Passenger>& destination) {
        eta = Etat::UNLOAD;

        for (const auto& p : passengers) {
            destination.push_back(p);
        }

        passengers.clear();
        std::cout << "[UNLOAD] Déchargement terminé." << std::endl;
    }
};