#ifndef CARD_H
#define CARD_H

#include <string>

enum class Suit {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

class Card {
public:
    Card(int rank, Suit suit);

    int getRank() const;
    Suit getSuit() const;
    std::string toString() const;

private:
    int rank;
    Suit suit;
};

#endif