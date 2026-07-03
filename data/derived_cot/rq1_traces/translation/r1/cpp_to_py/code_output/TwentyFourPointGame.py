import random
import math

class Calculator:
    def __init__(self):
        self.operators = {
            '+': lambda x, y: x + y,
            '-': lambda x, y: x - y,
            '*': lambda x, y: x * y,
            '/': lambda x, y: x / y,
            '^': lambda x, y: math.pow(x, y)
        }
    
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
        operand_stack = operand_stack[:]
        operator_stack = operator_stack[:]
        op = operator_stack.pop()
        operand2 = operand_stack.pop()
        operand1 = operand_stack.pop()
        operation = self.operators.get(op)
        if operation is None:
            raise ValueError(f"Unknown operator: {op}")
        result = operation(operand1, operand2)
        operand_stack.append(result)
        return operand_stack, operator_stack
        
    def calculate(self, expression):
        if not expression:
            return 0.0
            
        operand_stack = []
        operator_stack = []
        num_buffer = ""
        
        for ch in expression:
            if ch.isdigit() or ch == '.':
                num_buffer += ch
            else:
                if num_buffer != "":
                    operand_stack.append(float(num_buffer))
                    num_buffer = ""
                    
                if ch in self.operators:
                    while (operator_stack and operator_stack[-1] != '(' and 
                           self.precedence(operator_stack[-1]) >= self.precedence(ch)):
                        operand_stack, operator_stack = self.apply_operator(operand_stack, operator_stack)
                    operator_stack.append(ch)
                    
                elif ch == '(':
                    operator_stack.append(ch)
                    
                elif ch == ')':
                    while operator_stack and operator_stack[-1] != '(':
                        operand_stack, operator_stack = self.apply_operator(operand_stack, operator_stack)
                    if operator_stack and operator_stack[-1] == '(':
                        operator_stack.pop()
        
        if num_buffer != "":
            operand_stack.append(float(num_buffer))
            
        while operator_stack:
            operand_stack, operator_stack = self.apply_operator(operand_stack, operator_stack)
            
        return operand_stack[-1] if operand_stack else 0.0

class TwentyFourPointGame:
    def __init__(self):
        self.nums = []
        random.seed()
    
    def generate_cards(self):
        self.nums = [random.randint(1, 9) for _ in range(4)]
    
    def get_my_cards(self):
        self.generate_cards()
        return self.nums
    
    def set_nums(self, now):
        self.nums = now
    
    def answer(self, expression):
        if expression == "pass":
            return self.get_my_cards()
        
        stat = {}
        for c in expression:
            if c.isdigit():
                num_val = int(c)
                if num_val in self.nums:
                    stat[c] = stat.get(c, 0) + 1
        
        nums_used = stat.copy()
        for num in self.nums:
            c = str(num)
            if c in nums_used and nums_used[c] > 0:
                nums_used[c] -= 1
            else:
                return []
                
        if any(nums_used[c] != 0 for c in nums_used):
            return []
            
        if self.evaluate_expression(expression):
            return [1]
        else:
            return []
    
    def evaluate_expression(self, expression):
        try:
            if len(expression) == 0:
                return False
            if expression[0] not in '0123456789(':
                return False
            if expression[-1] not in '0123456789)':
                return False
                
            calculator = Calculator()
            ans = calculator.calculate(expression)
            return abs(ans - 24.0) < 1e-9
            
        except Exception:
            return False