#ifndef FLAT_BONUS_MODIFIER_H
#define FLAT_BONUS_MODIFIER_H

#include "IModifier.h"
#include <string>

class FlatBonusModifier : public IModifier {
public:
    std::string getName() const override;
    int apply(int baseScore) override;
};

#endif