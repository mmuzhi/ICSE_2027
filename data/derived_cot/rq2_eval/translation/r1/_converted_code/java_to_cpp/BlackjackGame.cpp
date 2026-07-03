#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

class BlackjackGame {
private:
    std::vector<std::string> deck;
    std::vector<std::string> playerHand;
    std::vector<std::string> dealerHand;

public:
    BlackjackGame();
    std::vector<std::string> createDeck();
    int calculate_hand_value(const std::vector<std::string>& hand);
    std::string check_winner(const std::vector<std::string>& playerHand, const std::vector<std::string>& dealerHand);
};

BlackjackGame::BlackjackGame() : deck(createDeck()), playerHand(), dealerHand() {}

std::vector<std::string> BlackjackGame::createDeck() {
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

int BlackjackGame::calculate_hand_value(const std::vector<std::string>& hand) {
    int value = 0;
    int numAces = 0;
    for (const auto& card : hand) {
        std::string rank = card.substr(0, card.length() - 1);
        if (rank == "A") {
            value += 11;
            numAces++;
        } else if (rank == "J" || rank == "Q" || rank == "K") {
            value += 10;
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

std::string BlackjackGame::check_winner(const std::vector<std::string>& playerHand, const std::vector<std::string>& dealerHand) {
    int playerValue = calculate_hand_value(playerHand);
    int dealerValue = calculate_hand_value(dealerHand);

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

int main() {
    BlackjackGame game;
    std::cout << "[";
    for (size_t i = 0; i < game.deck.size(); ++i) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << game.deck[i];
    }
    std::cout << "]" << std::endl;

    std::vector<std::string> hand = {"QD", "9D", "JC", "QH", "AS"};
    std::cout << game.calculate_hand_value(hand) << std::endl;

    std::vector<std::string> playerHand = {"QD", "9D", "JC", "QH", "AS"};
    std::vector<std::string> dealerHand = {"QD", "9D", "JC", "QH", "2S"};
    std::cout << game.check_winner(playerHand, dealerHand) << std::endl;

    return 0;
}