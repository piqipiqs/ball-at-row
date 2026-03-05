#ifndef SCORING_SYSTEM_H
#define SCORING_SYSTEM_H

#include <vector>
#include <string>
#include "Card.h"

struct ScoreResult {
    int baseScore;        // jumlah nilai kartu
    int finalScore;       // baseScore * multiplier (dibulatkan)
    double multiplier;    // 1.0, 1.5, 2.0
    std::string combo;    // "Two Pair", "Pair", "High Card"
};

class ScoringSystem {
public:
    ScoreResult evaluate(const std::vector<Card>& hand) const;

private:
    int calculateBaseScore(const std::vector<Card>& hand) const;
    int countPairs(const std::vector<Card>& hand) const; // hitung berapa pasang rank
};

#endif