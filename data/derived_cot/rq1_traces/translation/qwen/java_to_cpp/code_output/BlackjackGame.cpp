#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <cctype>

class BlackjackGame {
private:
    std::vector<std::string> deck;
    std::vector<std::string> playerHand;
    std::vector<std::string> dealerHand;

    std::vector<std::string> createDeck() {
        std::vector<std::string> deck;
        std::string suits[] = {"S", "C", "D", "H"};
        std::string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        for (const auto& suit : suits) {
            for (const auto& rank : ranks) {
                deck.push_back(rank + suit);
            }
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(deck.begin(), deck.end(), g);
        return deck;
    }

    int calculateHandValue(const std::vector<std::string>& hand) {
        int value = 0;
        int numAces = 0;
        for (const auto& card : hand) {
            std::string rank = card.substr(0, card.size() - 1);
            if (rank == "J" || rank == "Q" || rank == "K") {
                value += 10;
            } else if (rank == "A") {
                value += 11;
                numAces++;
            } else {
                value += std::stoi(rank);
            }
        }
        while (value > 21 && numAces > 0) {
            value -= 10;
            numAces--;
        }
        return value;
    }

public:
    BlackjackGame() : deck(createDeck()) {
        playerHand.clear();
        dealerHand.clear();
    }

    std::string checkWinner(const std::vector<std::string>& playerHand, const std::vector<std::string>& dealerHand) {
        int playerValue = calculateHandValue(playerHand);
        int dealerValue = calculateHandValue(dealerHand);
        if (playerValue > 21 && dealerValue > 21) {
            return playerValue <= dealerValue ? "Player wins" : "Dealer wins";
        } else if (playerValue > 21) {
            return "Dealer wins";
        } else if (dealerValue > 21) {
            return "Player wins";
        } else {
            return playerValue > dealerValue ? "Player wins" : "Dealer wins";
        }
    }

    static void main(int argc, char* argv[]) {
        BlackjackGame game;
        std::cout << "Deck: ";
        for (const auto& card : game.deck) {
            std::cout << card << " ";
        }
        std::cout << "\n";
        std::cout << "Hand value: " << game.calculateHandValue(std::vector<std::string>{"QD", "9D", "JC", "QH", "AS"}) << "\n";
        std::cout << "Winner: " << game.checkWinner(std::vector<std::string>{"QD", "9D", "JC", "QH", "AS"}, std::vector<std::string>{"QD", "9D", "JC", "QH", "2S"}) << "\n";
    }
};

int main(int argc, char* argv[]) {
    BlackjackGame::main(argc, argv);
    return 0;
}