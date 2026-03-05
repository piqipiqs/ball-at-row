#include <iostream>
#include <limits>

using namespace std;

void showMenu() {
    cout << "\n";
    cout << "      BALL AT ROW (C++)    \n";
    cout << "\n";
    cout << "1. Start Game\n";
    cout << "2. Exit\n";
    cout << "=============================\n";
    cout << "Choose: ";
}

void startGame() {
    cout << "\nGame Started!\n";
    cout << "Press Enter to return to menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    int choice;
    bool running = true;

    while (running) {
        system("cls"); // Windows (hapus layar)
        // kalau Linux/Mac ganti jadi: system("clear");

        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            startGame();
            break;
        case 2:
            cout << "\nExiting game...\n";
            running = false;
            break;
        default:
            cout << "\nInvalid choice!\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    return 0;
}