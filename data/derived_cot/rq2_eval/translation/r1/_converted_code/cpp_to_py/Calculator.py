import math

def safe_div(x, y):
    try:
        return x / y
    except ZeroDivisionError:
        if x != x:  # Check if x is NaN
            return float('nan')
        if x == 0:
            return float('nan')
        if (x < 0) != (y < 0):
            return -float('inf')
        else:
            return float('inf')

def safe_pow(x, y):
    try:
        return x ** y
    except ZeroDivisionError:
        if x == 0 and y < 0:
            k = -y
            if k.is_integer():
                if math.copysign(1, x) < 0 and int(k) % 2 == 1:
                    return -float('inf')
                else:
                    return float('inf')
            else:
                return float('inf')
        else:
            raise

class Calculator:
    def __init__(self):
        self.operators = {
            '+': lambda x, y: x + y,
            '-': lambda x, y: x - y,
            '*': lambda x, y: x * y,
            '/': safe_div,
            '^': safe_pow
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
        op_stack_copy = operator_stack[:]
        operand_stack_copy = operand_stack[:]
        op = op_stack_copy.pop()
        operand2 = operand_stack_copy.pop()
        operand1 = operand_stack_copy.pop()
        if op not in self.operators:
            raise ValueError(f"Unknown operator: {op}")
        func = self.operators[op]
        result = func(operand1, operand2)
        operand_stack_copy.append(result)
        return operand_stack_copy, op_stack_copy

    def calculate(self, expression):
        if not expression:
            return 0.0
        operand_stack = []
        operator_stack = []
        num_buffer = ''
        for ch in expression:
            if ch.isdigit() or ch == '.':
                num_buffer += ch
            else:
                if num_buffer:
                    operand_stack.append(float(num_buffer))
                    num_buffer = ''
                if ch in ['+', '-', '*', '/', '^']:
                    while (operator_stack and 
                           operator_stack[-1] != '(' and 
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
        if num_buffer:
            operand_stack.append(float(num_buffer))
        while operator_stack:
            operand_stack, operator_stack = self.apply_operator(operand_stack, operator_stack)
        return operand_stack[-1] if operand_stack else 0.0