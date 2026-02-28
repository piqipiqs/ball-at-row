#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

#include <vector>
#include "Card.h"

class ScoreSystem {
public:
    int calculateScore(const std::vector<Card>& hand);
};

#endif