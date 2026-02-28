#include "Deck.h"
#include <algorithm>
#include <random>

Deck::Deck() {
    std::string suits[] = {"Hearts","Diamonds","Clubs","Spades"};
    std::string ranks[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};

    for (auto& s : suits)
        for (auto& r : ranks)
            cards.emplace_back(r, s);
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::draw() {
    Card c = cards.back();
    cards.pop_back();
    return c;
}