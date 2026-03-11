#include <iostream>
#include <vector>
#include <string>

class Card {
public:
    std::string name;

    Card(std::string n) : name(n) {}
};

class Deck {
public:
    void Shuffle() {
        std::cout << "[Deck] Shuffling deck...\n";
    }

    std::vector<Card> DrawHand(int count) {
        std::vector<Card> hand;
        for (int i = 0; i < count; i++) {
            hand.push_back(Card("Card_" + std::to_string(i + 1)));
        }
        return hand;
    }
};

class ScoringSystem {
public:
    int Evaluate(const std::vector<Card>& selectedCards) {
        std::cout << "[ScoringSystem] Evaluating selected cards...\n";
        return static_cast<int>(selectedCards.size()) * 10; // placeholder
    }
};

class RunSession {
private:
    Deck deck;
    ScoringSystem scoringSystem;

    int roundScore = 0;
    int targetScore = 50;
    int handsLeft = 3;
    bool gameOver = false;

public:
    void StartRun() {
        std::cout << "=== Start Run ===\n";
        deck.Shuffle();

        while (!IsGameOver()) {
            PlayerActionPhase();
            ResolveSystemPhase();
            RewardPhase();
            UpdateStatePhase();
            CheckRoundStatePhase();
            std::cout << "----------------------\n";
        }

        std::cout << "=== Run Ended ===\n";
    }

private:
    std::vector<Card> currentHand;
    std::vector<Card> selectedCards;
    int lastScore = 0;

    bool IsGameOver() {
        return gameOver;
    }

    void PlayerActionPhase() {
        std::cout << "[Phase 1] Player receives cards and selects action\n";
        currentHand = deck.DrawHand(5);

        std::cout << "Player hand: ";
        for (const auto& card : currentHand) {
            std::cout << card.name << " ";
        }
        std::cout << "\n";

        // Placeholder: player selects first 3 cards
        selectedCards.clear();
        for (int i = 0; i < 3 && i < (int)currentHand.size(); i++) {
            selectedCards.push_back(currentHand[i]);
        }

        std::cout << "Player selects 3 cards.\n";
    }

    void ResolveSystemPhase() {
        std::cout << "[Phase 2] System evaluates selected cards\n";
        lastScore = scoringSystem.Evaluate(selectedCards);
        std::cout << "Score gained: " << lastScore << "\n";
    }

    void RewardPhase() {
        std::cout << "[Phase 3] Reward / progress is applied\n";
        roundScore += lastScore;
        std::cout << "Current round score: " << roundScore << "/" << targetScore << "\n";
    }

    void UpdateStatePhase() {
        std::cout << "[Phase 4] Updating game state\n";
        handsLeft--;
        std::cout << "Hands left: " << handsLeft << "\n";
    }

    void CheckRoundStatePhase() {
        std::cout << "[Phase 5] Checking round state\n";

        if (roundScore >= targetScore) {
            std::cout << "Round cleared!\n";
            gameOver = true; // placeholder end
        } else if (handsLeft <= 0) {
            std::cout << "No hands left. Game Over.\n";
            gameOver = true;
        } else {
            std::cout << "Continue playing...\n";
        }
    }
};

int main() {
    RunSession session;
    session.StartRun();
    return 0;
}