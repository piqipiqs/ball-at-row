#include "ShopSystem.h"
#include "ModifierFactory.h"

#include <iostream>
#include <limits>

static void clearBadInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ShopSystem::openShop(
    int& coins,
    int& handsPerRound,
    int& discardsPerRound,
    double& comboUpgradeBonus,
    std::vector<std::unique_ptr<IModifier>>& modifiers
) {
    const int COST_HAND = 10;
    const int COST_DISCARD = 8;
    const int COST_COMBO = 12;
    const int COST_MODIFIER = 15;

    ModifierFactory factory;

    while (true) {
        std::cout << "\nSHOP\n";
        std::cout << "Coins: " << coins << "\n";
        std::cout << "1. +1 Hand        (" << COST_HAND << ")\n";
        std::cout << "2. +1 Discard     (" << COST_DISCARD << ")\n";
        std::cout << "3. Combo upgrade  (" << COST_COMBO << ")\n";
        std::cout << "4. Modifier       (" << COST_MODIFIER << ")\n";
        std::cout << "5. Skip\n";

        std::cout << "\nOwned Modifiers:\n";
        if (modifiers.empty()) {
            std::cout << "  (none)\n";
        } else {
            for (const auto& m : modifiers) {
                std::cout << "  - " << m->getName() << "\n";
            }
        }

        std::cout << "\nChoose: ";
        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            clearBadInput();
            std::cout << "Invalid input.\n";
            continue;
        }

        if (choice == 5) {
            std::cout << "Skip shop.\n";
            return;
        }

        if (choice == 1) {
            if (coins < COST_HAND) { std::cout << "Not enough coins.\n"; continue; }
            coins -= COST_HAND;
            handsPerRound++;
            std::cout << "Purchased +1 Hand. Hands per round: " << handsPerRound << "\n";
        }
        else if (choice == 2) {
            if (coins < COST_DISCARD) { std::cout << "Not enough coins.\n"; continue; }
            coins -= COST_DISCARD;
            discardsPerRound++;
            std::cout << "Purchased +1 Discard. Discards per round: " << discardsPerRound << "\n";
        }
        else if (choice == 3) {
            if (coins < COST_COMBO) { std::cout << "Not enough coins.\n"; continue; }
            coins -= COST_COMBO;
            comboUpgradeBonus += 0.10;
            std::cout << "Combo upgraded! Global bonus: +" << comboUpgradeBonus << "x\n";
        }
        else if (choice == 4) {
            if (coins < COST_MODIFIER) { std::cout << "Not enough coins.\n"; continue; }
            coins -= COST_MODIFIER;

            auto mod = factory.createRandom();
            std::cout << "You got modifier: " << mod->getName() << "\n";
            modifiers.push_back(std::move(mod));
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }
}