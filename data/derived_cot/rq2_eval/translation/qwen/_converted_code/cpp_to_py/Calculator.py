from collections import deque

class Calculator:
    def __init__(self):
        self.operators = {
            '+': lambda x, y: x + y,
            '-': lambda x, y: x - y,
            '*': lambda x, y: x * y,
            '/': lambda x, y: x / y,
            '^': lambda x, y: x ** y
        }
    
    def calculate(self, expression):
        if not expression:
            return 0.0
        
        operand_stack = deque()
        operator_stack = deque()
        num_buffer = ''
        
        for ch in expression:
            if ch.isdigit() or ch == '.':
                num_buffer += ch
            else:
                if num_buffer:
                    operand_stack.append(float(num_buffer))
                    num_buffer = ''
                
                if ch in '+-*/^':
                    while (operator_stack and operator_stack[-1] != '(' and
                           self.precedence(operator_stack[-1]) >= self.precedence(ch)):
                        self.apply_operator(operand_stack, operator_stack)
                    operator_stack.append(ch)
                elif ch == '(':
                    operator_stack.append(ch)
                elif ch == ')':
                    while operator_stack and operator_stack[-1] != '(':
                        self.apply_operator(operand_stack, operator_stack)
                    if operator_stack and operator_stack[-1] == '(':
                        operator_stack.pop()
        
        if num_buffer:
            operand_stack.append(float(num_buffer))
        
        while operator_stack:
            self.apply_operator(operand_stack, operator_stack)
        
        return operand_stack[-1] if operand_stack else 0.0
    
    def precedence(self, op):
        if op in '+-':
            return 1
        elif op in '*/':
            return 2
        elif op == '^':
            return 3
        return 0
    
    def apply_operator(self, operand_stack, operator_stack):
        if not operator_stack:
            return
        
        op = operator_stack.pop()
        operand2 = operand_stack.pop()
        operand1 = operand_stack.pop()
        
        result = self.operators[op](operand1, operand2)
        operand_stack.append(result)

# Example usage:
# calc = Calculator()
# print(calc.calculate("2+3*4"))  # Output: 14.0