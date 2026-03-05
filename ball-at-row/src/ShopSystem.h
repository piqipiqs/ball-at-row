#ifndef SHOP_SYSTEM_H
#define SHOP_SYSTEM_H

#include <vector>
#include <memory>
#include "modifiers/IModifier.h"

class ShopSystem {
public:
    void openShop(
        int& coins,
        int& handsPerRound,
        int& discardsPerRound,
        double& comboUpgradeBonus,
        std::vector<std::unique_ptr<IModifier>>& modifiers
    );
};

#endif