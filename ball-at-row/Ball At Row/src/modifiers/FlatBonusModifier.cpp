#include "FlatBonusModifier.h"

int FlatBonusModifier::apply(int baseScore) {
    return baseScore + 50;
}