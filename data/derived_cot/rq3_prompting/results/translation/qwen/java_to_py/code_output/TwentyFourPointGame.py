import random
import re

class TwentyFourPointGame:
    def __init__(self):
        self.nums = self.getMyCards()

    def getMyCards(self):
        cards = [random.randint(1, 9) for _ in range(4)]
        return cards

    def answer(self, expression):
        if expression == "pass":
            self.nums = self.getMyCards()
            return False

        expr_digits = re.findall(r'\d', expression)
        total_digits = len(expr_digits)

        # If the expression contains non-digit characters other than operators and parentheses, return False
        if re.search(r'[^0-9\+\-\*\/\(\)\.]', expression):
            return False

        # Count occurrences of each digit in the expression
        digit_count = [0] * 10
        for digit in expr_digits:
            digit_count[int(digit)] += 1

        # Check if the expression uses exactly the four numbers, each exactly once
        for num in self.nums:
            if digit_count[num] != 1:
                return False

        return self.evaluateExpression(expression)

    def evaluateExpression(self, expression):
        try:
            class Parser:
                def __init__(self, expr):
                    self.expr = expr
                    self.pos = -1
                    self.ch = -1
                    self.nextChar()

                def nextChar(self):
                    self.pos += 1
                    if self.pos < len(self.expr):
                        self.ch = self.expr[self.pos]
                    else:
                        self.ch = -1

                def eat(self, charToEat):
                    while self.ch == ' ':
                        self.nextChar()
                    if self.ch == charToEat:
                        self.nextChar()
                        return True
                    return False

                def parse(self):
                    nextChar = self.nextChar
                    eat = self.eat
                    pos = self.pos
                    ch = self.ch

                    def parseExpression():
                        x = parseTerm()
                        while eat('+'):
                            x += parseTerm()
                        while eat('-'):
                            x -= parseTerm()
                        return x

                    def parseTerm():
                        x = parseFactor()
                        while eat('*'):
                            x *= parseFactor()
                        while eat('/'):
                            x /= parseFactor()
                        return x

                    def parseFactor():
                        if eat('+'):
                            return parseFactor()
                        if eat('-'):
                            return -parseFactor()

                        startPos = pos
                        if eat('('):
                            x = parseExpression()
                            eat(')')
                        elif ch >= '0' and ch <= '9' or ch == '.':
                            while (ch >= '0' and ch <= '9') or ch == '.':
                                nextChar()
                            try:
                                x = float(self.expr[startPos:self.pos])
                            except ValueError:
                                raise ValueError("Invalid number format")
                        else:
                            raise ValueError(f"Unexpected character: {ch}")

                        return x

                    result = parseExpression()
                    if pos < len(self.expr):
                        raise ValueError(f"Unexpected character: {self.ch}")
                    return result

            parser = Parser(expression)
            return abs(parser.parse() - 24) < 1e-10
        except Exception:
            return False

    def getNums(self):
        return self.nums