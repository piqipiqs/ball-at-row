#include "FlatBonusModifier.h"

std::string FlatBonusModifier::getName() const {
    return "Flat Bonus (+50)";
}

int FlatBonusModifier::apply(int baseScore) {
    return baseScore + 50;
}