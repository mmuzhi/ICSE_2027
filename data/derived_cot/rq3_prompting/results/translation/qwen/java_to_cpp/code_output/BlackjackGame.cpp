#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <random>
#include <cctype>

class BlackjackGame {
private:
    std::vector<std::string> deck;
    std::vector<std::string> playerHand;
    std::vector<std::string> dealerHand;

    std::vector<std::string> createDeck() {
        std::vector<std::string> deck;
        const std::string suits[] = {"S", "C", "D", "H"};
        const std::string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        
        for (const std::string& suit : suits) {
            for (const std::string& rank : ranks) {
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
            std::string rank = card.substr(0, card.length() - 1);
            if (rank.find_first_of("0123456789") != std::string::npos) {
                value += std::stoi(rank);
            }
            else if (rank == "J" || rank == "Q" || rank == "K") {
                value += 10;
            }
            else if (rank == "A") {
                value += 11;
                numAces++;
            }
        }
        while (value > 21 && numAces > 0) {
            value -= 10;
            numAces--;
        }
        return value;
    }

    std::string checkWinner(const std::vector<std::string>& playerHand, const std::vector<std::string>& dealerHand) {
        int playerValue = calculateHandValue(playerHand);
        int dealerValue = calculateHandValue(dealerHand);
        if (playerValue > 21 && dealerValue > 21) {
            return playerValue <= dealerValue ? "Player wins" : "Dealer wins";
        }
        else if (playerValue > 21) {
            return "Dealer wins";
        }
        else if (dealerValue > 21) {
            return "Player wins";
        }
        else {
            return playerValue > dealerValue ? "Player wins" : "Dealer wins";
        }
    }

public:
    BlackjackGame() {
        deck = createDeck();
        playerHand.clear();
        dealerHand.clear();
    }
};

int main() {
    BlackjackGame game;
    std::cout << "Deck: ";
    for (const auto& card : game.deck) {
        std::cout << card << " ";
    }
    std::cout << "\nHand value: " << game.calculateHandValue({"QD", "9D", "JC", "QH", "AS"}) << std::endl;
    std::cout << game.checkWinner({"QD", "9D", "JC", "QH", "AS"}, {"QD", "9D", "JC", "QH", "2S"}) << std::endl;
    return 0;
}