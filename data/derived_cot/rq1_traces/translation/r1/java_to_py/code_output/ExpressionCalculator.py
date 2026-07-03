import collections

class ExpressionCalculator:
    def __init__(self):
        self.postfix_stack = collections.deque()
    
    def calculate(self, expression):
        transformed = self.transform(expression)
        self.prepare(transformed)
        return self.evaluate_postfix()
    
    def transform(self, expression):
        expr = expression.replace(" ", "")
        expr = expr.replace("-", "~")
        if expr.startswith("~(") and len(expr) > 2:
            return "0-" + expr[1:]
        return expr
    
    def prepare(self, expression):
        self.postfix_stack.clear()
        operator_stack = collections.deque()
        n = len(expression)
        i = 0
        while i < n:
            ch = expression[i]
            if ch.isdigit() or ch == '.':
                num = []
                j = i
                while j < n and (expression[j].isdigit() or expression[j] == '.'):
                    num.append(expression[j])
                    j += 1
                self.postfix_stack.append(''.join(num))
                i = j - 1
            elif ch == '(':
                operator_stack.append(ch)
            elif ch == ')':
                while operator_stack and operator_stack[-1] != '(':
                    self.postfix_stack.append(operator_stack.pop())
                if operator_stack:
                    operator_stack.pop()
            elif self.is_operator(ch):
                while operator_stack and operator_stack[-1] != '(' and self.is_operator(operator_stack[-1]) and not self.compare(operator_stack[-1], ch):
                    self.postfix_stack.append(operator_stack.pop())
                operator_stack.append(ch)
            i += 1
        
        while operator_stack:
            self.postfix_stack.append(operator_stack.pop())
    
    def is_operator(self, ch):
        return ch in ['+', '-', '*', '/', '%']
    
    def compare(self, op1, op2):
        op1_mapped = '/' if op1 == '%' else op1
        op2_mapped = '/' if op2 == '%' else op2
        priority = [0, 3, 2, 1, -1, 1, 0, 2]
        idx1 = ord(op1_mapped) - 40
        idx2 = ord(op2_mapped) - 40
        if idx1 < 0 or idx1 >= len(priority) or idx2 < 0 or idx2 >= len(priority):
            return False
        return priority[idx2] >= priority[idx1]
    
    def evaluate_postfix(self):
        stack = collections.deque()
        for token in self.postfix_stack:
            if len(token) == 1 and self.is_operator(token[0]):
                b = stack.pop()
                a = stack.pop()
                stack.append(self._calculate(a, b, token[0]))
            else:
                stack.append(float(token))
        return stack.pop()
    
    def _calculate(self, a, b, operator):
        if operator == '+':
            return a + b
        elif operator == '-':
            return a - b
        elif operator == '*':
            return a * b
        elif operator == '/':
            return a / b
        elif operator == '%':
            return a % b
        else:
            raise ValueError(f"Unsupported operator: {operator}")