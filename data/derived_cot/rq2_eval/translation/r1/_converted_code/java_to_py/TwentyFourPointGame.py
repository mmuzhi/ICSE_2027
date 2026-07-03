import random

class TwentyFourPointGame:

    def __init__(self):
        self.nums = self.get_my_cards()

    def get_my_cards(self):
        return [random.randint(1, 9) for _ in range(4)]

    def answer(self, expression):
        if expression == 'pass':
            self.nums = self.get_my_cards()
            return False
        counts = [0] * 10
        for char in expression:
            if char.isdigit():
                digit = int(char)
                counts[digit] += 1
        for num in self.nums:
            if counts[num] > 0:
                counts[num] -= 1
            else:
                return False
        for count in counts:
            if count != 0:
                return False
        return self.evaluate_expression(expression)

    def evaluate_expression(self, expression):
        try:

            class ExprParser:

                def __init__(self, expr):
                    self.expr = expr
                    self.pos = -1
                    self.ch = None

                def next_char(self):
                    self.pos += 1
                    if self.pos < len(self.expr):
                        self.ch = self.expr[self.pos]
                    else:
                        self.ch = -1

                def eat(self, char_to_eat):
                    while self.ch == ' ':
                        self.next_char()
                    if self.ch == char_to_eat:
                        self.next_char()
                        return True
                    return False

                def parse(self):
                    self.next_char()
                    x = self.parse_expression()
                    if self.pos < len(self.expr):
                        raise RuntimeError(f'Unexpected: {self.ch}')
                    return x

                def parse_expression(self):
                    x = self.parse_term()
                    while True:
                        if self.eat('+'):
                            x += self.parse_term()
                        elif self.eat('-'):
                            x -= self.parse_term()
                        else:
                            return x

                def parse_term(self):
                    x = self.parse_factor()
                    while True:
                        if self.eat('*'):
                            x *= self.parse_factor()
                        elif self.eat('/'):
                            x /= self.parse_factor()
                        else:
                            return x

                def parse_factor(self):
                    if self.eat('+'):
                        return self.parse_factor()
                    if self.eat('-'):
                        return -self.parse_factor()
                    start_pos = self.pos
                    if self.eat('('):
                        x = self.parse_expression()
                        self.eat(')')
                        return x
                    elif self.ch is not None and (self.ch >= '0' and self.ch <= '9' or self.ch == '.'):
                        while self.ch is not None and (self.ch >= '0' and self.ch <= '9' or self.ch == '.'):
                            self.next_char()
                        num_str = self.expr[start_pos:self.pos]
                        return float(num_str)
                    elif self.ch == -1:
                        raise RuntimeError('Unexpected end of input')
                    else:
                        raise RuntimeError(f'Unexpected character: {self.ch}')
            parser = ExprParser(expression)
            result = parser.parse()
            return result == 24.0
        except Exception as e:
            return False

    def _generate_cards(self):
        return self.nums