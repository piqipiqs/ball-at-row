#include "ModifierFactory.h"
#include "modifiers/DoubleScoreModifier.h"
#include "modifiers/FlatBonusModifier.h"

IModifier* ModifierFactory::createModifier(int choice) {
    if (choice == 1) return new DoubleScoreModifier();
    if (choice == 2) return new FlatBonusModifier();
    return nullptr;
}