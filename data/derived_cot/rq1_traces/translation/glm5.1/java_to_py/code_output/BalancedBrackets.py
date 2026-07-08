class BalancedBrackets:
    def __init__(self, expr: str):
        self.stack = []
        self.left_brackets = "({["
        self.right_brackets = ")}]"
        self.expr = expr

    def clear_expr(self) -> None:
        cleaned_expr = []
        for c in self.expr:
            if c in self.left_brackets or c in self.right_brackets:
                cleaned_expr.append(c)
        self.expr = "".join(cleaned_expr)

    def check_balanced_brackets(self) -> bool:
        self.clear_expr()
        for brkt in self.expr:
            if brkt in self.left_brackets:
                self.stack.append(brkt)
            else:
                if not self.stack:
                    return False
                current_brkt = self.stack.pop()
                if current_brkt == '(' and brkt != ')':
                    return False
                if current_brkt == '{' and brkt != '}':
                    return False
                if current_brkt == '[' and brkt != ']':
                    return False
        return not self.stack

    def get_expr(self) -> str:
        return self.expr


if __name__ == "__main__":
    b = BalancedBrackets("a(b)c")
    print(b.check_balanced_brackets())