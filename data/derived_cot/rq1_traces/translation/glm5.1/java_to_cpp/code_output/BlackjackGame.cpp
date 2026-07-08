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
        std::vector<std::string> deck;
        const std::string suits[] = {"S", "C", "D", "H"};
        const std::string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        
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
            std::string rank = card.substr(0, card.length() - 1);
            
            // Equivalent to Java's rank.matches("\\d+")
            bool isDigit = !rank.empty() && std::all_of(rank.begin(), rank.end(), 
                [](unsigned char c) { return std::isdigit(c); });
                
            if (isDigit) {
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

// Helper function to mimic Java's ArrayList.toString() output format
std::string listToString(const std::vector<std::string>& list) {
    std::string result = "[";
    for (size_t i = 0; i < list.size(); ++i) {
        if (i > 0) {
            result += ", ";
        }
        result += list[i];
    }
    result += "]";
    return result;
}

int main() {
    BlackjackGame game;
    
    std::cout << listToString(game.deck) << std::endl;
    std::cout << game.calculateHandValue({"QD", "9D", "JC", "QH", "AS"}) << std::endl;
    std::cout << game.checkWinner({"QD", "9D", "JC", "QH", "AS"}, {"QD", "9D", "JC", "QH", "2S"}) << std::endl;
    
    return 0;
}