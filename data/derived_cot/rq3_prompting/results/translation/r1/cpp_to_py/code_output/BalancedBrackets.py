class BalancedBrackets:
    def __init__(self, expr: str):
        self.expr = expr
        self.leftBrackets = "({["
        self.rightBrackets = ")}]"
        self.stack = []

    def clearExpr(self):
        # Remove all characters that are not brackets
        self.expr = ''.join(
            c for c in self.expr
            if c in self.leftBrackets or c in self.rightBrackets
        )

    def check_balanced_brackets(self) -> bool:
        self.clearExpr()
        for brkt in self.expr:
            if brkt in self.leftBrackets:
                self.stack.append(brkt)
            else:
                if not self.stack:
                    return False
                current = self.stack.pop()
                if (current == '(' and brkt != ')') or \
                   (current == '{' and brkt != '}') or \
                   (current == '[' and brkt != ']'):
                    return False
        return not self.stack