#include "Game.h"
#include <iostream>
#include <limits>

Game::Game() {
    state = GameState::MENU; 
    running = true;
}

void Game::run() {
    while (running) {
        system("cls"); 

        switch (state) {
        case GameState::MENU:
            menuState();
            break;
        case GameState::PLAY:
            playState();
            break;
        case GameState::GAMEOVER:
            gameOverState();
            break;
        }
    }
}

void Game::menuState() {
    std::cout << "\n";
    std::cout << "      BALL AT ROW (C++)    \n";
    std::cout << "\n";
    std::cout << "1. Start Game\n";
    std::cout << "2. Exit\n";
    std::cout << "Choose: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        deck = Deck();
        deck.shuffle();
        hand.clear();
        state = GameState::PLAY;
    }
    else if (choice == 2) {
        running = false; 
    }
}

void Game::playState() {
    for (int i = 0; i < 5; i++)
        hand.push_back(deck.draw());

    std::cout << "\nYour Cards:\n";
    for (auto& c : hand)
        std::cout << c.toString() << "\n";

    std::cout << "\nPress Enter...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    state = GameState::GAMEOVER;
}

void Game::gameOverState() {
    std::cout << "\nGame Over\n";
    std::cout << "Press Enter to return to menu...";
    std::cin.get();

    state = GameState::MENU; 
}