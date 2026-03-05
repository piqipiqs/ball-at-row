#ifndef FLAT_BONUS_MODIFIER_H
#define FLAT_BONUS_MODIFIER_H

#include "IModifier.h"

class FlatBonusModifier : public IModifier {
public:
    int apply(int baseScore) override;
};

#endif