class BalancedBrackets:
    def __init__(self, expr):
        self.expr = expr
        self.stack = []
        self.leftBrackets = "({["
        self.rightBrackets = ")}]"

    def clearExpr(self):
        self.expr = ''.join(filter(lambda c: c in self.leftBrackets or c in self.rightBrackets, self.expr))

    def check_balanced_brackets(self):
        self.clearExpr()
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