#include "Card.h"

Card::Card(std::string r, std::string s) : rank(r), suit(s) {}

std::string Card::getRank() const { return rank; }
std::string Card::getSuit() const { return suit; }

int Card::getValue() const {
    if (rank == "A") return 14;
    if (rank == "K") return 13;
    if (rank == "Q") return 12;
    if (rank == "J") return 11;
    return std::stoi(rank);
}

std::string Card::toString() const {
    return rank + " of " + suit;
}