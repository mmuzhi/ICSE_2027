import re
from collections import deque

class ExpressionCalculator:
    def __init__(self):
        self.postfix_stack = deque()

    def calculate(self, expression):
        transformed_expression = self.transform(expression)
        self.prepare(transformed_expression)
        return self.evaluate_postfix()

    def prepare(self, expression):
        self.postfix_stack.clear()
        operator_stack = deque()
        i = 0
        n = len(expression)
        while i < n:
            char = expression[i]
            if char.isdigit() or char == '.':
                num_str = ''
                while i < n and (char.isdigit() or char == '.'):
                    num_str += char
                    i += 1
                self.postfix_stack.append(num_str)
                continue
            elif char == '(':
                operator_stack.append(char)
            elif char == ')':
                while operator_stack and operator_stack[-1] != '(':
                    self.postfix_stack.append(operator_stack.pop())
                operator_stack.pop()
            elif self.is_operator(char):
                while operator_stack and self.is_operator(operator_stack[-1]) and not self.compare(operator_stack[-1], char):
                    self.postfix_stack.append(operator_stack.pop())
                operator_stack.append(char)
            i += 1
        while operator_stack:
            self.postfix_stack.append(operator_stack.pop())

    def is_operator(self, ch):
        return ch in "+-*/%"

    def compare(self, op1, op2):
        # Map modulus to division for precedence comparison
        op1_mapped = '/' if op1 == '%' else op1
        op2_mapped = '/' if op2 == '%' else op2
        precedence = {
            '+': 2,
            '-': 1,
            '*': -1,
            '/': 1,
            '%': 1  # Map to division's precedence
        }
        return precedence[op2_mapped] >= precedence[op1_mapped]

    def evaluate_postfix(self):
        stack = deque()
        for token in self.postfix_stack:
            if self.is_operator(token[0]):
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

    def transform(self, expression):
        expression = expression.replace(" ", "")
        expression = expression.replace("-", "~")
        if expression.startswith('~') and len(expression) > 1 and expression[1] == '(':
            expression = '0' + expression.replace('~', '-', 1)
        return expression