import random
import re
import math

class TwentyFourPointGame:
    def __init__(self):
        self.nums = []
        random.seed(int(time.time()))

    def generate_cards(self):
        for _ in range(4):
            self.nums.append(random.randint(1, 9))
        assert len(self.nums) == 4

    def get_my_cards(self):
        self.nums = []
        self.generate_cards()
        return self.nums

    def answer(self, expression):
        if expression == "pass":
            return self.get_my_cards()
        
        # Count occurrences of each digit in the expression that are in self.nums
        expr_digits = [int(c) for c in expression if c.isdigit()]
        count_map = {}
        for num in expr_digits:
            count_map[num] = count_map.get(num, 0) + 1
        
        # Check if all four numbers are used exactly once
        if len(count_map) != 4:
            return []
        for num in self.nums:
            if num not in count_map or count_map[num] != 1:
                return []
        
        # Evaluate the expression
        if self.evaluate_expression(expression):
            return [1]
        else:
            return []

    def evaluate_expression(self, expression):
        try:
            if expression.startswith('(') and expression.endswith(')'):
                expression = expression[1:-1]
            elif not expression.startswith('(') and not expression.isdigit():
                return False
            elif not expression.endswith(')') and not expression.isdigit():
                return False
            
            calculator = Calculator()
            result = calculator.calculate(expression)
            return math.isclose(result, 24.0, abs_tol=1e-7)
        except Exception:
            return False

    def set_nums(self, now):
        self.nums = now


class Calculator:
    def __init__(self):
        self.operators = {
            '+': lambda x, y: x + y,
            '-': lambda x, y: x - y,
            '*': lambda x, y: x * y,
            '/': lambda x, y: x / y,
            '^': lambda x, y: math.pow(x, y)
        }

    def calculate(self, expression):
        if not expression:
            raise ValueError("Empty expression")
        
        operand_stack = []
        operator_stack = []
        num_buffer = ""
        
        # Regular expression to validate the expression format
        valid_pattern = r'^[\d\.\+\-\*\/\(\)]+$'
        if not re.match(valid_pattern, expression):
            raise ValueError("Invalid characters in expression")
        
        for char in expression:
            if char in '0123456789.':
                num_buffer += char
            else:
                if num_buffer:
                    operand_stack.append(float(num_buffer))
                    num_buffer = ""
                
                if char in '+-*/^':
                    while operator_stack and operator_stack[-1] != '(':
                        if self._should_apply_operator(operator_stack[-1], char):
                            self._apply_operator(operand_stack, operator_stack)
                    operator_stack.append(char)
                elif char == '(':
                    operator_stack.append(char)
                elif char == ')':
                    while operator_stack and operator_stack[-1] != '(':
                        self._apply_operator(operand_stack, operator_stack)
                    if operator_stack and operator_stack[-1] == '(':
                        operator_stack.pop()
        
        if num_buffer:
            operand_stack.append(float(num_buffer))
        
        while operator_stack:
            self._apply_operator(operand_stack, operator_stack)
        
        if operand_stack:
            return operand_stack[-1]
        raise ValueError("Invalid expression")
    
    def _should_apply_operator(self, op1, op2):
        if op2 in '+-':
            return True
        elif op2 in '*/':
            return op1 not in '*/'
        elif op2 == '^':
            return op1 != '^'
        return False
    
    def _apply_operator(self, operand_stack, operator_stack):
        if not operand_stack or len(operand_stack) < 2:
            raise ValueError("Insufficient operands")
        
        op = operator_stack.pop()
        b = operand_stack.pop()
        a = operand_stack.pop()
        
        result = self.operators[op](a, b)
        operand_stack.append(result)


import time

if __name__ == "__main__":
    game = TwentyFourPointGame()
    game.generate_cards()
    print("Your cards:", game.nums)
    user_input = input("Enter your expression: ")
    result = game.answer(user_input)
    print("Result:", result)