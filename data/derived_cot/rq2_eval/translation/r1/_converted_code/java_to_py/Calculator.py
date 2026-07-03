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
        operand_stack = []
        operator_stack = []
        num_buffer = []
        
        i = 0
        n = len(expression)
        while i < n:
            ch = expression[i]
            if ch.isdigit() or ch == '.':
                num_buffer.append(ch)
                i += 1
            else:
                if num_buffer:
                    operand_stack.append(float(''.join(num_buffer)))
                    num_buffer = []
                
                if ch in self.operators:
                    while (operator_stack and operator_stack[-1] != '(' and 
                           self.precedence(operator_stack[-1]) >= self.precedence(ch)):
                        self.apply_operator(operand_stack, operator_stack)
                    operator_stack.append(ch)
                    i += 1
                elif ch == '(':
                    operator_stack.append(ch)
                    i += 1
                elif ch == ')':
                    while operator_stack and operator_stack[-1] != '(':
                        self.apply_operator(operand_stack, operator_stack)
                    if operator_stack and operator_stack[-1] == '(':
                        operator_stack.pop()
                    i += 1
                else:
                    i += 1
        
        if num_buffer:
            operand_stack.append(float(''.join(num_buffer)))
        
        while operator_stack:
            self.apply_operator(operand_stack, operator_stack)
        
        return operand_stack[-1] if operand_stack else None

    def precedence(self, operator):
        if operator in ['+', '-']:
            return 1
        elif operator in ['*', '/']:
            return 2
        elif operator == '^':
            return 3
        else:
            return 0

    def apply_operator(self, operand_stack, operator_stack):
        operator = operator_stack.pop()
        operand2 = operand_stack.pop()
        operand1 = operand_stack.pop()
        result = self.operators[operator](operand1, operand2)
        operand_stack.append(result)

def main():
    calculator = Calculator()
    print(calculator.calculate("1+2-3"))

if __name__ == "__main__":
    main()