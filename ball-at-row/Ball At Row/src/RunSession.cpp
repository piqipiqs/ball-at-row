#include "RunSession.h"

#include "Deck.h"
#include "ScoringSystem.h"
#include "Card.h"

#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>
#include <sstream>
#include <string>

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

// Baca input 1 baris: "1 2 5" (1-based), min 1 max 5 kartu, unik, range 1..7
static std::vector<int> chooseIndicesFromLine_1Based(int maxPick, int maxIndex) {
    while (true) {
        std::cout << "Pick Cards (1-" << maxIndex << ", max " << maxPick << "): ";

        std::string line;
        std::getline(std::cin >> std::ws, line); // >> ws buang whitespace/newline sisa

        if (line.empty()) {
            std::cout << "Please type at least 1 number.\n";
            continue;
        }

        std::istringstream iss(line);
        std::vector<int> idx;
        int x;

        while (iss >> x) {
            idx.push_back(x);
        }

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

// Discard kartu yang dipilih dari offered, lalu draw pengganti sampai kembali 7
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
    const int targetScore[TOTAL_ROUND] = { 100, 150, 200 };

    const int HANDS_PER_ROUND = 3;
    const int DISCARD_PER_ROUND = 2;

    ScoringSystem scoring;

    for (int round = 1; round <= TOTAL_ROUND; round++) {

        Deck deck;            // reset deck tiap round
        deck.shuffle();

        std::cout << "\n=============================\n";
        std::cout << "ROUND " << round << " | Target: " << targetScore[round - 1] << "\n";
        std::cout << "Hands: " << HANDS_PER_ROUND << " | Discard chances: " << DISCARD_PER_ROUND << "\n";
        std::cout << "=============================\n";

        int discardsLeft = DISCARD_PER_ROUND;
        int roundTotalScore = 0;

        for (int handNum = 1; handNum <= HANDS_PER_ROUND; handNum++) {
            std::cout << "\n--- Hand " << handNum << "/" << HANDS_PER_ROUND << " ---\n";
            std::cout << "Discards left (this round): " << discardsLeft << "\n";

            std::vector<Card> offered = dealOffered7(deck);

            while (true) {
                // 1) tampilkan 7 kartu
                printOffered(offered);

                // 2) user langsung pilih kartu (ENTER selesai)
                std::vector<int> idx = chooseIndicesFromLine_1Based(5, (int)offered.size());
                std::vector<Card> chosen = selectCards(offered, idx);

                std::cout << "Selected Cards: ";
                printLine(chosen);

                // 3) baru muncul pilihan play/discard
                char action = askPlayOrDiscardSelected(discardsLeft);

                if (action == 'D') {
                    discardsLeft--;
                    discardSelected(offered, idx, deck);
                    std::cout << "Discarded selected cards! (Offered updated)\n\n";
                    continue; // balik lagi pilih kartu dari offered terbaru
                }

                // PLAY
                ScoreResult result = scoring.evaluate(chosen);

                std::cout << "Combo      : " << result.combo << "\n";
                std::cout << "Base Score : " << result.baseScore << "\n";
                std::cout << "Multiplier : x" << result.multiplier << "\n";
                std::cout << "Final Score: " << result.finalScore << "\n";

                roundTotalScore += result.finalScore;

                // progress target n/n setiap selesai play
                std::cout << "Target Progress: " << roundTotalScore
                          << " / " << targetScore[round - 1] << "\n";

                break; // lanjut hand berikutnya
            }
        }

        std::cout << "\n=== ROUND " << round << " TOTAL ===\n";
        std::cout << "Total Score: " << roundTotalScore << "\n";
        std::cout << "Target     : " << targetScore[round - 1] << "\n";

        if (roundTotalScore >= targetScore[round - 1]) {
            std::cout << "ROUND " << round << " CLEARED \n";
        } else {
            std::cout << "ROUND " << round << " FAILED \n";
            std::cout << "\n=== END RUN ===\n";
            return;
        }
    }

    std::cout << "\n=== END RUN ===\n";
    std::cout << "You cleared all rounds! \n";
}