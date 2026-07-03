import random

class TwentyFourPointGame:

    def __init__(self):
        self.nums = self.get_my_cards()

    def get_my_cards(self):
        cards = []
        for _ in range(4):
            cards.append(random.randint(1, 9))
        return cards

    def answer(self, expression):
        if expression == 'pass':
            self.nums = self.get_my_cards()
            return False
        counts = [0] * 10
        for char in expression:
            if char.isdigit():
                num = int(char)
                counts[num] += 1
        for num in self.nums:
            if counts[num] == 0:
                return False
            counts[num] -= 1
        for count in counts:
            if count != 0:
                return False
        expression_clean = expression.replace(' ', '')
        try:
            result = eval(expression_clean)
            return result == 24.0
        except:
            return False

    def _generate_cards(self):
        return self.nums