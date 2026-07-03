#include <vector>
#include <string>
#include <algorithm>
#include <random>

class BlackjackGame {
private:
    std::vector<std::string> deck;
    std::vector<std::string> player_hand;
    std::vector<std::string> dealer_hand;

    void create_deck() {
        std::vector<std::string> suits = {"S", "C", "D", "H"};
        std::vector<std::string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        std::vector<std::string> temp_deck;
        for (char s : suits) {
            for (const std::string& r : ranks) {
                temp_deck.push_back(r + s);
            }
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(temp_deck.begin(), temp_deck.end(), gen);
        deck = temp_deck;
    }

    int calculate_hand_value(const std::vector<std::string>& hand) {
        int value = 0;
        int num_aces = 0;
        for (const auto& card : hand) {
            std::string rank_str = card.substr(0, card.size() - 1);
            if (rank_str == "A") {
                value += 11;
                num_aces++;
            } else if (rank_str == "J" || rank_str == "Q" || rank_str == "K") {
                value += 10;
            } else if (std::all_of(rank_str.begin(), rank_str.end(), [](unsigned char c) { return std::isdigit(c); })) {
                value += std::stoi(rank_str);
            }
        }
        while (value > 21 && num_aces > 0) {
            value -= 10;
            num_aces--;
        }
        return value;
    }

public:
    BlackjackGame() {
        create_deck();
    }

    int check_winner(const std::vector<std::string>& player_hand, const std::vector<std::string>& dealer_hand) {
        int player_value = calculate_hand_value(player_hand);
        int dealer_value = calculate_hand_value(dealer_hand);
        if (player_value > 21 && dealer_value > 21) {
            return player_value <= dealer_value ? 0 : 1;
        } else if (player_value > 21) {
            return 1;
        } else if (dealer_value > 21) {
            return 0;
        } else {
            return player_value <= dealer_value ? 1 : 0;
        }
    }
};