#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
private:
    std::string rank;
    std::string suit;

public:
    Card(std::string r, std::string s);
    std::string getRank() const;
    std::string getSuit() const;
    int getValue() const;
    std::string toString() const;
};

#endif