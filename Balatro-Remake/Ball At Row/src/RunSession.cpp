#include "RunSession.h"
#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <vector>

void RunSession::startRun() {
    std::cout << "\n=== START RUN ===\n";

    const int TOTAL_ROUND = 3;

    for (int round = 1; round <= TOTAL_ROUND; round++) {
        std::cout << "\n--- ROUND " << round << " ---\n";

        // =========================
        // 1. PLAY HAND (CARD & DECK)
        // =========================
        Deck deck;
        deck.shuffle();

        std::vector<Card> hand;
        for (int i = 0; i < 5; i++) {
            hand.push_back(deck.draw());
        }

        std::cout << "Hand: ";
        for (const auto& card : hand) {
            std::cout << card.toString() << " ";
        }
        std::cout << "\n";

        // =========================
        // 2. CALCULATE SCORE (DUMMY)
        // =========================
        int score = 100; // skor dasar sementara
        std::cout << "Score: " << score << "\n";

        // =========================
        // 3. SHOP (SIMULASI)
        // =========================
        std::cout << "Entering shop...\n";
    }

    std::cout << "\n=== END RUN ===\n";
}