import random

class TwentyFourPointGame:
    def __init__(self):
        self.nums = self.get_my_cards()

    def get_my_cards(self):
        return [random.randint(1, 9) for _ in range(4)]

    def answer(self, expression):
        if expression == "pass":
            self.nums = self.get_my_cards()
            return False

        counts = [0] * 10
        for ch in expression:
            if '0' <= ch <= '9':
                counts[ord(ch) - ord('0')] += 1

        for num in self.nums:
            if counts[num] > 0:
                counts[num] -= 1
            else:
                return False

        if any(c != 0 for c in counts):
            return False

        return self.evaluate_expression(expression)

    def evaluate_expression(self, expression):
        class Parser:
            def __init__(self, s):
                self.s = s
                self.pos = -1
                self.ch = None
                self._next()

            def _next(self):
                self.pos += 1
                if self.pos < len(self.s):
                    self.ch = self.s[self.pos]
                else:
                    self.ch = None

            def eat(self, c):
                while self.ch is not None and self.ch == ' ':
                    self._next()
                if self.ch == c:
                    self._next()
                    return True
                return False

            def parse(self):
                self._next()
                x = self._parse_expression()
                if self.ch is not None:
                    raise Exception("Unexpected: " + str(self.ch))
                return x

            def _parse_expression(self):
                x = self._parse_term()
                while True:
                    if self.eat('+'):
                        x += self._parse_term()
                    elif self.eat('-'):
                        x -= self._parse_term()
                    else:
                        return x

            def _parse_term(self):
                x = self._parse_factor()
                while True:
                    if self.eat('*'):
                        x *= self._parse_factor()
                    elif self.eat('/'):
                        x /= self._parse_factor()
                    else:
                        return x

            def _parse_factor(self):
                if self.eat('+'):
                    return self._parse_factor()
                if self.eat('-'):
                    return -self._parse_factor()

                if self.eat('('):
                    x = self._parse_expression()
                    self.eat(')')
                    return x

                start_pos = self.pos
                if self.ch is not None and (('0' <= self.ch <= '9') or self.ch == '.'):
                    while self.ch is not None and (('0' <= self.ch <= '9') or self.ch == '.'):
                        self._next()
                    x = float(self.s[start_pos:self.pos])
                    return x
                else:
                    raise Exception("Unexpected: " + str(self.ch))

        try:
            return Parser(expression).parse() == 24.0
        except Exception:
            return False

    def get_nums(self):
        return self.nums