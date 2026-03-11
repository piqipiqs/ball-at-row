#include "DoubleScoreModifier.h"

std::string DoubleScoreModifier::getName() const {
    return "Double Score (x2)";
}

int DoubleScoreModifier::apply(int baseScore) {
    return baseScore * 2;
}