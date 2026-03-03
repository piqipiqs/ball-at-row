#include "Card.h"

Card::Card(int rank, Suit suit) : rank(rank), suit(suit) {}

int Card::getRank() const { return rank; }
Suit Card::getSuit() const { return suit; }

// A=1 ... K=13
int Card::getScoreValue() const {
    return rank;
}

std::string Card::toString() const {
    std::string r;
    if (rank == 1) r = "A";
    else if (rank >= 2 && rank <= 10) r = std::to_string(rank);
    else if (rank == 11) r = "J";
    else if (rank == 12) r = "Q";
    else r = "K"; // 13

    std::string s;
    switch (suit) {
        case Suit::HEARTS:   s = "H"; break;
        case Suit::DIAMONDS: s = "D"; break;
        case Suit::CLUBS:    s = "C"; break;
        case Suit::SPADES:   s = "S"; break;
    }

    return r + s;
}