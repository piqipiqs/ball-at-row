#include "GameState.h"
#include "MainMenu.h"
#include "RunSession.h"

int main() {
    GameState state = GameState::MENU;

    MainMenu menu;
    RunSession run;

    while (state != GameState::EXIT) {

        if (state == GameState::MENU) {
            state = menu.show(); // kalau pilih 1, harus berubah ke PLAY
        }
        else if (state == GameState::PLAY) {
            run.startRun();      // ini jalankan game
            state = GameState::MENU; // selesai run, balik ke menu
        }
    }

    return 0;
}