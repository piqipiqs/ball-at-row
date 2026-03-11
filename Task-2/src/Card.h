#ifndef CARD_H
#define CARD_H

#include <string>

enum class Suit {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

// rank: 1..13 (A=1, J=11, Q=12, K=13)
class Card {
public:
    Card(int rank, Suit suit);

    int getRank() const;
    Suit getSuit() const;

    int getScoreValue() const;     // <- nilai skor kartu sesuai aturan
    std::string toString() const;  // <- contoh: "AH", "10D", "KS"

private:
    int rank;
    Suit suit;
};

#endif