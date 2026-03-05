#ifndef DOUBLE_SCORE_MODIFIER_H
#define DOUBLE_SCORE_MODIFIER_H

#include "IModifier.h"
#include <string>

class DoubleScoreModifier : public IModifier {
public:
    std::string getName() const override;
    int apply(int baseScore) override;
};

#endif