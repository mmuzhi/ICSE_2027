import random
from collections import Counter

class Calculator:
    def __init__(self):
        self.operators = {
            '+': lambda a, b: a + b,
            '-': lambda a, b: a - b,
            '*': lambda a, b: a * b,
            '/': lambda a, b: a / b,
            '^': lambda a, b: a ** b
        }
    
    def calculate(self, expression):
        if not expression:
            return 0.0
        
        operand_stack = []
        operator_stack = []
        num_buffer = ''
        
        for char in expression:
            if char.isdigit() or char == '.':
                num_buffer += char
            else:
                if num_buffer:
                    operand_stack.append(float(num_buffer))
                    num_buffer = ''
                
                if char in '+-*/^':
                    while operator_stack and operator_stack[-1] != '(' and \
                          self.precedence(operator_stack[-1]) >= self.precedence(char):
                        operand_stack, operator_stack = self.apply_operator(operand_stack, operator_stack)
                    operator_stack.append(char)
                elif char == '(':
                    operator_stack.append(char)
                elif char == ')':
                    while operator_stack and operator_stack[-1] != '(':
                        operand_stack, operator_stack = self.apply_operator(operand_stack, operator_stack)
                    if operator_stack and operator_stack[-1] == '(':
                        operator_stack.pop()
        
        if num_buffer:
            operand_stack.append(float(num_buffer))
        
        while operator_stack:
            operand_stack, operator_stack = self.apply_operator(operand_stack, operator_stack)
        
        return operand_stack[-1] if operand_stack else 0.0

    def precedence(self, op):
        if op in ['+', '-']:
            return 1
        elif op in ['*', '/']:
            return 2
        elif op == '^':
            return 3
        else:
            return 0

    def apply_operator(self, operand_stack, operator_stack):
        op = operator_stack.pop()
        b = operand_stack.pop()
        a = operand_stack.pop()
        
        result = self.operators[op](a, b)
        operand_stack.append(result)
        return operand_stack, operator_stack

class TwentyFourPointGame:
    def __init__(self):
        self.nums = []
    
    def generate_cards(self):
        self.nums = [random.randint(1, 9) for _ in range(4)]
    
    def get_my_cards(self):
        self.generate_cards()
        return self.nums
    
    def set_nums(self, now):
        self.nums = now
    
    def answer(self, expression):
        if expression == "pass":
            self.generate_cards()
            return self.nums
        
        expr_digits = [char for char in expression if char.isdigit()]
        expr_counter = Counter(expr_digits)
        card_counter = Counter(str(num) for num in self.nums)
        
        for num in self.nums:
            digit = str(num)
            if expr_counter.get(digit, 0) <= 0:
                return []
            expr_counter[digit] -= 1
        
        if expression[0] not in '0123456789(' or expression[-1] not in '0123456789)':
            return []
        
        try:
            if self.evaluate_expression(expression):
                return [1]
            else:
                return []
        except:
            return []
    
    def evaluate_expression(self, expression):
        calculator = Calculator()
        try:
            if expression[0] not in '0123456789(':
                raise ValueError("Invalid expression start")
            if expression[-1] not in '0123456789)':
                raise ValueError("Invalid expression end")
            result = calculator.calculate(expression)
            if abs(result - 24.0) < 1e-10:
                return True
            else:
                return False
        except Exception as e:
            return False