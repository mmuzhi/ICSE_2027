import random
import sys

class BlackjackGame:
    def __init__(self):
        self.deck = self.create_deck()
        self.player_hand = []
        self.dealer_hand = []
    
    def create_deck(self):
        suits = ["S", "C", "D", "H"]
        ranks = ["A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"]
        deck = [rank + suit for suit in suits for rank in ranks]
        
        # Use SystemRandom for non-deterministic shuffling if available
        try:
            rng = random.SystemRandom()
        except:
            rng = random
            
        rng.shuffle(deck)
        return deck

    def calculate_hand_value(self, hand):
        value = 0
        num_aces = 0
        
        for card in hand:
            rank = card[:-1]
            if rank in ["J", "Q", "K"]:
                value += 10
            elif rank == "A":
                value += 11
                num_aces += 1
            else:
                value += int(rank)
        
        while value > 21 and num_aces > 0:
            value -= 10
            num_aces -= 1
            
        return value

    def check_winner(self):
        player_value = self.calculate_hand_value(self.player_hand)
        dealer_value = self.calculate_hand_value(self.dealer_hand)
        
        if player_value > 21 and dealer_value > 21:
            return "Dealer wins" if dealer_value <= player_value else "Player wins"
        elif player_value > 21:
            return "Dealer wins"
        elif dealer_value > 21:
            return "Player wins"
        else:
            return "Dealer wins" if dealer_value >= player_value else "Player wins"