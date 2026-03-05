#ifndef SHOP_SYSTEM_H
#define SHOP_SYSTEM_H

#include <vector>
#include "modifiers/IModifier.h"

class ShopSystem {
public:
    void openShop(std::vector<IModifier*>& modifiers);
};

#endif