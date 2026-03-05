#include "MainMenu.h"
#include "RunSession.h"
#include "GameState.h"

int main() {
    GameState state = GameState::MENU;
    MainMenu menu;
    RunSession run;

    while (state != GameState::EXIT) {
        if (state == GameState::MENU) {
            state = menu.show();
        }
        else if (state == GameState::PLAY) {
            run.startRun();
            state = GameState::MENU; // balik ke menu
        }
    }

    return 0;
}