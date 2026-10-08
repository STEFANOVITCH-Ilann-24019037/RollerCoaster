#include <iostream>
#include <vector>
#include <string>

enum class Etat
{
    Board,
    Unboard
};
class Passenger {
public:
    std::string nom;
    Etat etat;
    Passenger(std::string n) : nom(n) {}
};