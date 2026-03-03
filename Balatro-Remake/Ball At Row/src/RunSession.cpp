#include "RunSession.h"

#include "Deck.h"
#include "ScoringSystem.h"   // <-- WAJIB, ini yang mencegah "incomplete type"
#include "Card.h"

#include <iostream>
#include <vector>
#include <set>
#include <limits>

static void clearBadInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static std::vector<Card> playerChooseCards_1Based(const std::vector<Card>& offered, int chooseCount) {
    std::cout << "Choose " << chooseCount << " cards to PLAY\n";

    // tampil 1-based
    for (int i = 0; i < (int)offered.size(); i++) {
        std::cout << "  [" << i + 1 << "] " << offered[i].toString() << "\n";
    }

    while (true) {
        std::cout << "Pick " << chooseCount << " Cards: ";

        std::vector<int> indices(chooseCount);
        for (int i = 0; i < chooseCount; i++) {
            std::cin >> indices[i];
        }

        if (std::cin.fail()) {
            clearBadInput();
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        bool valid = true;
        std::set<int> uniqueCheck;

        // konversi 1-based -> 0-based & validasi
        for (int &idx : indices) {
            idx--; // convert

            if (idx < 0 || idx >= (int)offered.size()) {
                valid = false;
                break;
            }
            uniqueCheck.insert(idx);
        }

        if (!valid || (int)uniqueCheck.size() != chooseCount) {
            std::cout << "Invalid or duplicate indices. Try again.\n";
            continue;
        }

        // ambil kartu sesuai urutan input pemain
        std::vector<Card> chosen;
        chosen.reserve(chooseCount);
        for (int idx : indices) {
            chosen.push_back(offered[idx]);
        }

        return chosen;
    }
}

void RunSession::startRun() {
    std::cout << "\n=== START RUN ===\n";

    const int TOTAL_ROUND = 3;
    const int targetScore[TOTAL_ROUND] = { 25, 30, 35 };

    Deck deck;
    deck.shuffle();

    ScoringSystem scoring; // <-- sekarang type-nya lengkap karena include ScoringSystem.h

    for (int round = 1; round <= TOTAL_ROUND; round++) {
        std::cout << "\n--- ROUND " << round << " ---\n";

        // 1) PLAY HAND: tawarkan 7 kartu, pemain pilih 5
        std::cout << "Dealing 7 cards...\n";
        std::vector<Card> offered;
        offered.reserve(7);
        for (int i = 0; i < 7; i++) {
            offered.push_back(deck.draw());
        }

        std::vector<Card> playedHand = playerChooseCards_1Based(offered, 5);

        std::cout << "Played Hand: ";
        for (const auto& c : playedHand) std::cout << c.toString() << " ";
        std::cout << "\n";

        // 2) CALCULATE SCORE + COMBO + MULTIPLIER
        ScoreResult result = scoring.evaluate(playedHand);

        std::cout << "Combo      : " << result.combo << "\n";
        std::cout << "Base Score : " << result.baseScore << "\n";
        std::cout << "Multiplier : x" << result.multiplier << "\n";
        std::cout << "Final Score: " << result.finalScore << "\n";
        std::cout << "Target     : " << targetScore[round - 1] << "\n";

        if (result.finalScore >= targetScore[round - 1]) {
            std::cout << "Result: WIN ROUND " << round << " \n";
        } else {
            std::cout << "Result: LOSE ROUND " << round << " \n";
            std::cout << "Run ended early.\n";
            std::cout << "\n=== END RUN ===\n";
            return;
        }

        // 3) SHOP (sementara)
        std::cout << "Entering shop...\n";
    }

    std::cout << "\n=== END RUN ===\n";
    std::cout << "You cleared all rounds! \n";
}