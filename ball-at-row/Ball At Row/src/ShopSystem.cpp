#include "ShopSystem.h"
#include "ModifierFactory.h"
#include <iostream>

void ShopSystem::openShop(std::vector<IModifier*>& modifiers) {
    std::cout << "Shop:\n1. Double Score\n2. Flat Bonus\n0. Skip\nChoice: ";
    int choice;
    std::cin >> choice;

    if (choice != 0) {
        IModifier* mod = ModifierFactory::createModifier(choice);
        if (mod) modifiers.push_back(mod);
    }
}