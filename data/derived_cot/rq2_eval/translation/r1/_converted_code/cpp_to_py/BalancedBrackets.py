class BalancedBrackets:

    def __init__(self, expr):
        self.stack = []
        self.leftBrackets = '({['
        self.rightBrackets = ')}]'
        self.expr = expr

    def clear_expr(self):
        self.expr = ''.join([c for c in self.expr if c in self.leftBrackets or c in self.rightBrackets])

    def check_balanced_brackets(self):
        self.clear_expr()
        mapping = {'(': ')', '{': '}', '[': ']'}
        for char in self.expr:
            if char in self.leftBrackets:
                self.stack.append(char)
            else:
                if not self.stack:
                    return False
                top_char = self.stack.pop()
                if mapping[top_char] != char:
                    return False
        return len(self.stack) == 0