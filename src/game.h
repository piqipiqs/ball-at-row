#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "ScoreSystem.h"
#include <vector>

enum class GameState {
    MENU,
    PLAY,
    GAMEOVER
};

class Game {
private:
    GameState state;
    bool running;

    Deck deck;
    ScoreSystem score;
    std::vector<Card> hand;

    void menuState();
    void playState();
    void gameOverState();

public:
    Game();
    void run();
};

#endif