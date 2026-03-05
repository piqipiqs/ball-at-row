#ifndef MODIFIER_FACTORY_H
#define MODIFIER_FACTORY_H

#include "modifiers/IModifier.h"

class ModifierFactory {
public:
    static IModifier* createModifier(int choice);
};

#endif