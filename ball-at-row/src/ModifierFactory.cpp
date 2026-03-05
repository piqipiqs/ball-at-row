#include "ModifierFactory.h"

#include "modifiers/FlatBonusModifier.h"
#include "modifiers/DoubleScoreModifier.h"

#include <random>
#include <memory>

std::unique_ptr<IModifier> ModifierFactory::createRandom() const
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, 2);

    int roll = dist(rng);

    if (roll == 1) return std::make_unique<FlatBonusModifier>();
    return std::make_unique<DoubleScoreModifier>();
}