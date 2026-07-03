#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <cctype>

class BlackjackGame {
public:
    std::vector<std::string> deck;
    std::vector<std::string> playerHand;
    std::vector<std::string> dealerHand;

    BlackjackGame() {
        deck = createDeck();
    }

    std::vector<std::string> createDeck() {
        std::vector<std::string> d;
        std::string suits[] = {"S", "C", "D", "H"};
        std::string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        for (const auto& suit : suits) {
            for (const auto& rank : ranks) {
                d.push_back(rank + suit);
            }
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(d.begin(), d.end(), g);
        return d;
    }

    int calculateHandValue(const std::vector<std::string>& hand) {
        int value = 0;
        int numAces = 0;
        for (const auto& card : hand) {
            std::string rank = card.substr(0, card.length() - 1);
            bool allDigits = !rank.empty();
            for (char c : rank) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    allDigits = false;
                    break;
                }
            }
            if (allDigits) {
                value += std::stoi(rank);
            } else if (rank == "J" || rank == "Q" || rank == "K") {
                value += 10;
            } else if (rank == "A") {
                value += 11;
                numAces += 1;
            }
        }
        while (value > 21 && numAces > 0) {
            value -= 10;
            numAces -= 1;
        }
        return value;
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
};

int main() {
    BlackjackGame game;
    std::cout << "[";
    for (size_t i = 0; i < game.deck.size(); i++) {
        if (i > 0) std::cout << ", ";
        std::cout << game.deck[i];
    }
    std::cout << "]" << std::endl;
    std::cout << game.calculateHandValue({"QD", "9D", "JC", "QH", "AS"}) << std::endl;
    std::cout << game.checkWinner({"QD", "9D", "JC", "QH", "AS"}, {"QD", "9D", "JC", "QH", "2S"}) << std::endl;
    return 0;
}