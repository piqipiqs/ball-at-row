#ifndef SCORING_SYSTEM_H
#define SCORING_SYSTEM_H

#include <vector>
#include <string>
#include "Card.h"

struct ScoreResult {
    int baseScore;
    int finalScore;
    double multiplier;
    std::string combo;
};

class ScoringSystem {
public:
    ScoreResult evaluate(const std::vector<Card>& hand) const;

private:
    int calculateBaseScore(const std::vector<Card>& hand) const;

    bool isFlush5(const std::vector<Card>& hand) const;
    bool isStraight5(const std::vector<Card>& hand) const;

    std::vector<int> rankCounts(const std::vector<Card>& hand) const;

    int pairCount(const std::vector<int>& counts) const;
    bool hasNKind(const std::vector<int>& counts, int n) const;
    bool isFullHouse(const std::vector<int>& counts) const;
};

#endif