#include "ScoringSystem.h"
#include <map>
#include <cmath>

int ScoringSystem::calculateBaseScore(const std::vector<Card>& hand) const {
    int total = 0;
    for (const auto& c : hand) total += c.getScoreValue(); // A=1 ... K=13
    return total;
}

int ScoringSystem::countPairs(const std::vector<Card>& hand) const {
    std::map<int, int> freq;
    for (const auto& c : hand) freq[c.getRank()]++;

    int pairs = 0;
    for (const auto& kv : freq) {
        if (kv.second == 2) pairs++;
    }
    return pairs;
}

ScoreResult ScoringSystem::evaluate(const std::vector<Card>& hand) const {
    ScoreResult res{};
    res.baseScore = calculateBaseScore(hand);

    int pairs = countPairs(hand);

    if (pairs >= 2) {
        res.combo = "Two Pair";
        res.multiplier = 2.0;
    } else if (pairs == 1) {
        res.combo = "Pair";
        res.multiplier = 1.5;
    } else {
        res.combo = "High Card";
        res.multiplier = 1.0;
    }

    res.finalScore = (int)std::lround(res.baseScore * res.multiplier);
    return res;
}