#include "ScoreSystem.h"
#include <map>
#include <algorithm>

int ScoreSystem::calculateScore(const std::vector<Card>& hand) {
    std::map<std::string, int> rankCount;
    std::map<std::string, int> suitCount;
    std::vector<int> values;

    for (auto& c : hand) {
        rankCount[c.getRank()]++;
        suitCount[c.getSuit()]++;
        values.push_back(c.getValue());
    }

    std::sort(values.begin(), values.end());

    // Pair
    for (auto& r : rankCount)
        if (r.second == 2)
            return 50;

    // Flush
    for (auto& s : suitCount)
        if (s.second == 5)
            return 100;

    // Straight
    bool straight = true;
    for (int i = 1; i < values.size(); i++)
        if (values[i] != values[i - 1] + 1)
            straight = false;

    if (straight)
        return 75;

    return 10; // High card
}