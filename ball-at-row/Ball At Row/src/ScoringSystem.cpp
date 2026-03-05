#include "ScoringSystem.h"
#include <cmath>
#include <algorithm>

int ScoringSystem::calculateBaseScore(const std::vector<Card>& hand) const {
    int total = 0;
    for (const auto& c : hand) total += c.getScoreValue();
    return total;
}

std::vector<int> ScoringSystem::rankCounts(const std::vector<Card>& hand) const {
    std::vector<int> counts(14, 0);
    for (const auto& c : hand) {
        int r = c.getRank();
        if (r >= 1 && r <= 13) counts[r]++;
    }
    return counts;
}

int ScoringSystem::pairCount(const std::vector<int>& counts) const {
    int p = 0;
    for (int r = 1; r <= 13; r++) if (counts[r] == 2) p++;
    return p;
}

bool ScoringSystem::hasNKind(const std::vector<int>& counts, int n) const {
    for (int r = 1; r <= 13; r++) if (counts[r] == n) return true;
    return false;
}

bool ScoringSystem::isFullHouse(const std::vector<int>& counts) const {
    bool has3 = false, has2 = false;
    for (int r = 1; r <= 13; r++) {
        if (counts[r] == 3) has3 = true;
        if (counts[r] == 2) has2 = true;
    }
    return has3 && has2;
}

bool ScoringSystem::isFlush5(const std::vector<Card>& hand) const {
    if ((int)hand.size() != 5) return false;
    Suit s = hand[0].getSuit();
    for (int i = 1; i < 5; i++) if (hand[i].getSuit() != s) return false;
    return true;
}

bool ScoringSystem::isStraight5(const std::vector<Card>& hand) const {
    if ((int)hand.size() != 5) return false;

    std::vector<int> ranks;
    ranks.reserve(5);
    for (const auto& c : hand) ranks.push_back(c.getRank());

    std::sort(ranks.begin(), ranks.end());
    ranks.erase(std::unique(ranks.begin(), ranks.end()), ranks.end());
    if ((int)ranks.size() != 5) return false;

    for (int i = 1; i < 5; i++) {
        if (ranks[i] != ranks[0] + i) return false;
    }
    return true;
}

ScoreResult ScoringSystem::evaluate(const std::vector<Card>& hand) const {
    ScoreResult res{};
    res.baseScore = calculateBaseScore(hand);

    res.combo = "High Card";
    res.multiplier = 1.0;

    if (hand.empty()) {
        res.finalScore = 0;
        return res;
    }

    auto counts = rankCounts(hand);
    int pairs = pairCount(counts);

    bool flush = isFlush5(hand);
    bool straight = isStraight5(hand);

    if (straight && flush) {
        res.combo = "Straight Flush";
        res.multiplier = 4.0;
    } else if (hasNKind(counts, 4)) {
        res.combo = "Four of a Kind";
        res.multiplier = 3.5;
    } else if (isFullHouse(counts)) {
        res.combo = "Full House";
        res.multiplier = 3.0;
    } else if (flush) {
        res.combo = "Flush";
        res.multiplier = 2.5;
    } else if (straight) {
        res.combo = "Straight";
        res.multiplier = 2.2;
    } else if (hasNKind(counts, 3)) {
        res.combo = "Three of a Kind";
        res.multiplier = 2.0;
    } else if (pairs >= 2) {
        res.combo = "Two Pair";
        res.multiplier = 1.7;
    } else if (pairs == 1) {
        res.combo = "Pair";
        res.multiplier = 1.4;
    } else {
        res.combo = "High Card";
        res.multiplier = 1.0;
    }

    res.finalScore = (int)std::lround(res.baseScore * res.multiplier);
    return res;
}