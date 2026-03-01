#include "Deck.h"
#include <algorithm>
#include <random>
#include <ctime>

Deck::Deck() {
    for (int s = 0; s < 4; s++) {
        for (int r = 2; r <= 14; r++) {
            cards.emplace_back(r, static_cast<Suit>(s));
        }
    }
}

void Deck::shuffle() {
    static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card Deck::draw() {
    Card top = cards.back();
    cards.pop_back();
    return top;
}