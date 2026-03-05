#include "Deck.h"
#include <algorithm>
#include <random>
#include <ctime>

Deck::Deck() {
    // 4 suit, rank 1..13 (A..K)
    for (int s = 0; s < 4; s++) {
        for (int r = 1; r <= 13; r++) {
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