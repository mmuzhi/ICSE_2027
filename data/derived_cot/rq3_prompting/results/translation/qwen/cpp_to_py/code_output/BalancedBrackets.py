class BalancedBrackets:
    leftBrackets = "({["
    rightBrackets = ")}]"

    def __init__(self, expr):
        self.expr = expr
        self.stack = []

    def clear_expr(self):
        allowed_chars = self.leftBrackets + self.rightBrackets
        self.expr = ''.join(filter(lambda c: c in allowed_chars, self.expr))

    def check_balanced_brackets(self):
        self.clear_expr()
        for char in self.expr:
            if char in self.leftBrackets:
                self.stack.append(char)
            else:
                if not self.stack:
                    return False
                top_char = self.stack.pop()
                if top_char == '(' and char != ')':
                    return False
                if top_char == '{' and char != '}':
                    return False
                if top_char == '[' and char != ']':
                    return False
        return len(self.stack) == 0