#include "RunSession.h"

#include "Deck.h"
#include "ScoringSystem.h"
#include "Card.h"
#include "ShopSystem.h"

#include "modifiers/IModifier.h"

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <string>
#include <memory>
#include <cmath>

static void printOffered(const std::vector<Card>& offered) {
    std::cout << "Offered Cards:\n";
    for (int i = 0; i < (int)offered.size(); i++) {
        std::cout << "  [" << i + 1 << "] " << offered[i].toString() << "\n";
    }
}

static void printLine(const std::vector<Card>& cards) {
    for (const auto& c : cards) std::cout << c.toString() << " ";
    std::cout << "\n";
}

static std::vector<Card> dealOffered7(Deck& deck) {
    std::vector<Card> offered;
    offered.reserve(7);
    for (int i = 0; i < 7; i++) offered.push_back(deck.draw());
    return offered;
}

// input 1 baris: "1 2 5" (1-based), min 1 max 5, unik, range 1..7
static std::vector<int> chooseIndicesFromLine_1Based(int maxPick, int maxIndex) {
    while (true) {
        std::cout << "Pick Cards (1-" << maxIndex << ", max " << maxPick << "): ";

        std::string line;
        std::getline(std::cin >> std::ws, line);

        if (line.empty()) {
            std::cout << "Please type at least 1 number.\n";
            continue;
        }

        std::istringstream iss(line);
        std::vector<int> idx;
        int x;

        while (iss >> x) idx.push_back(x);

        if (idx.empty()) {
            std::cout << "Invalid input. Example: 1 2 5\n";
            continue;
        }

        if ((int)idx.size() > maxPick) {
            std::cout << "Too many cards. Max is " << maxPick << ".\n";
            continue;
        }

        bool valid = true;
        std::set<int> uniq;

        for (int &v : idx) {
            v--; // 1-based -> 0-based
            if (v < 0 || v >= maxIndex) { valid = false; break; }
            uniq.insert(v);
        }

        if (!valid || (int)uniq.size() != (int)idx.size()) {
            std::cout << "Invalid range or duplicate indices.\n";
            continue;
        }

        return idx; // urutan sesuai input user
    }
}

static std::vector<Card> selectCards(const std::vector<Card>& offered, const std::vector<int>& idx) {
    std::vector<Card> chosen;
    chosen.reserve(idx.size());
    for (int x : idx) chosen.push_back(offered[x]);
    return chosen;
}

static void discardSelected(std::vector<Card>& offered, const std::vector<int>& idx, Deck& deck) {
    std::vector<int> sorted = idx;
    std::sort(sorted.begin(), sorted.end(), std::greater<int>());

    for (int pos : sorted) {
        offered.erase(offered.begin() + pos);
    }

    while ((int)offered.size() < 7) {
        offered.push_back(deck.draw());
    }
}

static char askPlayOrDiscardSelected(int discardsLeft) {
    while (true) {
        std::cout << "Selected Action: (P) Play";
        if (discardsLeft > 0) std::cout << " / (D) Discard Selected";
        std::cout << " : ";

        std::string line;
        std::getline(std::cin >> std::ws, line);
        if (line.empty()) continue;

        char c = line[0];
        if (c == 'P' || c == 'p') return 'P';
        if ((c == 'D' || c == 'd') && discardsLeft > 0) return 'D';

        std::cout << "Invalid action.\n";
    }
}

void RunSession::startRun() {
    std::cout << "\n=== START RUN ===\n";

    const int TOTAL_ROUND = 3;
    const int targetScore[TOTAL_ROUND] = { 50, 100, 200 };

    // base coin per round
    const int baseCoin[TOTAL_ROUND] = { 10, 15, 25 };

    // bisa di-upgrade di shop
    int handsPerRound = 4;
    int discardsPerRound = 3;

    // combo upgrade global (tambahan multiplier)
    double comboUpgradeBonus = 0.0;

    // modifier dari shop
    std::vector<std::unique_ptr<IModifier>> modifiers;

    int coins = 0;

    ScoringSystem scoring;
    ShopSystem shop;

    for (int round = 1; round <= TOTAL_ROUND; round++) {

        // reset deck tiap round
        Deck deck;
        deck.shuffle();

        std::cout << "\n=============================\n";
        std::cout << "ROUND " << round
                  << " | Target: " << targetScore[round - 1]
                  << " | Base Coin: " << baseCoin[round - 1] << "\n";
        std::cout << "Hands: " << handsPerRound
                  << " | Discard chances: " << discardsPerRound << "\n";
        std::cout << "Coins: " << coins << "\n";
        std::cout << "Combo Upgrade Bonus: +" << comboUpgradeBonus << "x\n";
        std::cout << "Modifiers owned: " << modifiers.size() << "\n";
        std::cout << "=============================\n";

        int discardsLeft = discardsPerRound;
        int roundTotalScore = 0;

        bool cleared = false;
        int lastPlayedCount = 0;

        for (int handNum = 1; handNum <= handsPerRound && !cleared; handNum++) {
            std::cout << "\n--- Hand " << handNum << "/" << handsPerRound << " ---\n";
            std::cout << "Discards left (this round): " << discardsLeft << "\n";

            std::vector<Card> offered = dealOffered7(deck);

            while (true) {
                printOffered(offered);

                std::vector<int> idx = chooseIndicesFromLine_1Based(5, (int)offered.size());
                std::vector<Card> chosen = selectCards(offered, idx);

                std::cout << "Selected Cards: ";
                printLine(chosen);

                char action = askPlayOrDiscardSelected(discardsLeft);

                if (action == 'D') {
                    discardsLeft--;
                    discardSelected(offered, idx, deck);
                    std::cout << "Discarded selected cards! (Offered updated)\n\n";
                    continue;
                }

                // PLAY
                lastPlayedCount = (int)chosen.size();
                ScoreResult result = scoring.evaluate(chosen);

                // apply combo upgrade bonus (bonus multiplier)
                int finalScore = (int)std::lround(result.baseScore * (result.multiplier + comboUpgradeBonus));

                // apply modifiers (IModifier::apply(int))
                for (auto& m : modifiers) {
                    finalScore = m->apply(finalScore);
                }

                std::cout << "Combo      : " << result.combo << "\n";
                std::cout << "Base Score : " << result.baseScore << "\n";
                std::cout << "Multiplier : x" << result.multiplier << " (+" << comboUpgradeBonus << ")\n";
                std::cout << "Final Score: " << finalScore << "\n";

                roundTotalScore += finalScore;

                std::cout << "Target Progress: "
                          << roundTotalScore << " / " << targetScore[round - 1] << "\n";

                if (roundTotalScore >= targetScore[round - 1]) {
                    cleared = true;
                }

                break; // selesai 1 hand
            }
        }

        if (!cleared) {
            std::cout << "\n=== ROUND " << round << " FAILED ❌ ===\n";
            std::cout << "Total Score: " << roundTotalScore << " / " << targetScore[round - 1] << "\n";
            std::cout << "Coins Now  : " << coins << "\n";
            std::cout << "\n=== END RUN ===\n";
            return;
        }

        // round cleared → coin reward: base + sisa kartu
        int leftover = 7 - lastPlayedCount;
        int earned = baseCoin[round - 1] + leftover;
        coins += earned;

        std::cout << "\n=== ROUND " << round << " CLEARED ✅ ===\n";
        std::cout << "Coin Earned: " << baseCoin[round - 1] << " + " << leftover
                  << " = " << earned << "\n";
        std::cout << "Coins Now  : " << coins << "\n";

        // SHOP setelah round
        shop.openShop(coins, handsPerRound, discardsPerRound, comboUpgradeBonus, modifiers);
    }

    std::cout << "\n=== END RUN ===\n";
    std::cout << "You cleared all rounds! 🎉\n";
    std::cout << "Final Coins: " << coins << "\n";
}