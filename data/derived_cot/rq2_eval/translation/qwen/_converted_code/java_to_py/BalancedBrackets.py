class BalancedBrackets:

    def __init__(self, expr):
        self.stack = []
        self.left_brackets = '({['
        self.right_brackets = ')}]'
        self.expr = expr

    def clear_expr(self):
        cleaned_chars = []
        for char in self.expr:
            if char in self.left_brackets or char in self.right_brackets:
                cleaned_chars.append(char)
        self.expr = ''.join(cleaned_chars)

    def check_balanced_brackets(self):
        self.clear_expr()
        matching_brackets = {')': '(', ']': '[', '}': '{'}
        for char in self.expr:
            if char in self.left_brackets:
                self.stack.append(char)
            else:
                if not self.stack:
                    return False
                top = self.stack.pop()
                if matching_brackets[char] != top:
                    return False
        return len(self.stack) == 0

    def get_expr(self):
        return self.expr
if __name__ == '__main__':
    b = BalancedBrackets('a(b)c')
    print(b.check_balanced_brackets())