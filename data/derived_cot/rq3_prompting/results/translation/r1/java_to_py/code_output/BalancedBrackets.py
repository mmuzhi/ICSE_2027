class BalancedBrackets:
    def __init__(self, expr: str):
        self.stack = []
        self.leftBrackets = "({["
        self.rightBrackets = ")}]"
        self.expr = expr

    def clearExpr(self):
        cleaned = []
        for c in self.expr:
            if c in self.leftBrackets or c in self.rightBrackets:
                cleaned.append(c)
        self.expr = "".join(cleaned)

    def checkBalancedBrackets(self):
        self.clearExpr()
        for brkt in self.expr:
            if brkt in self.leftBrackets:
                self.stack.append(brkt)
            else:
                if not self.stack:
                    return False
                current = self.stack.pop()
                if current == '(' and brkt != ')':
                    return False
                if current == '{' and brkt != '}':
                    return False
                if current == '[' and brkt != ']':
                    return False
        return not self.stack

    def getExpr(self):
        return self.expr


if __name__ == "__main__":
    b = BalancedBrackets("a(b)c")
    print(b.checkBalancedBrackets())