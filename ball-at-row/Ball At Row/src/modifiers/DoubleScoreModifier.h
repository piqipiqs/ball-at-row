#ifndef DOUBLE_SCORE_MODIFIER_H
#define DOUBLE_SCORE_MODIFIER_H

#include "IModifier.h"

class DoubleScoreModifier : public IModifier {
public:
    int apply(int baseScore) override;
};

#endif