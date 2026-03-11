#ifndef MODIFIER_FACTORY_H
#define MODIFIER_FACTORY_H

#include <memory>
#include "modifiers/IModifier.h"

class ModifierFactory {
public:
    std::unique_ptr<IModifier> createRandom() const;
};

#endif