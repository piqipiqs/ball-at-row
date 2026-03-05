#include "MainMenu.h"
#include <iostream>

GameState MainMenu::show() {
    int choice;

    std::cout << "\n BALL AT ROW \n";
    std::cout << "1. Start Game\n";
    std::cout << "2. Exit\n";
    std::cout << "Choose: ";
    std::cin >> choice;

    if (choice == 1)
        return GameState::PLAY;
    else
        return GameState::EXIT;
}