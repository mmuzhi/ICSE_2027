class Calculator:
    def __init__(self):
        self.operators = {
            '+': lambda x, y: x + y,
            '-': lambda x, y: x - y,
            '*': lambda x, y: x * y,
            '/': lambda x, y: x / y,
            '^': lambda x, y: x ** y
        }

    def precedence(self, op):
        if op == '+' or op == '-':
            return 1
        if op == '*' or op == '/':
            return 2
        if op == '^':
            return 3
        return 0

    def apply_operator(self, operand_stack, operator_stack):
        op = operator_stack.pop()
        operand2 = operand_stack.pop()
        operand1 = operand_stack.pop()
        result = self.operators[op](operand1, operand2)
        operand_stack.append(result)

    def calculate(self, expression):
        operand_stack = []
        operator_stack = []
        num_buffer = []

        if expression == "":
            return None

        for ch in expression:
            if ch in '0123456789.':
                num_buffer.append(ch)
            else:
                if num_buffer:
                    num_str = ''.join(num_buffer)
                    try:
                        num = float(num_str)
                    except ValueError:
                        raise ValueError("Invalid number format")
                    operand_stack.append(num)
                    num_buffer = []
                if ch in self.operators:
                    while (operator_stack and 
                           operator_stack[-1] != '(' and 
                           self.precedence(operator_stack[-1]) >= self.precedence(ch)):
                        self.apply_operator(operand_stack, operator_stack)
                    operator_stack.append(ch)
                elif ch == '(':
                    operator_stack.append(ch)
                elif ch == ')':
                    while operator_stack and operator_stack[-1] != '(':
                        self.apply_operator(operand_stack, operator_stack)
                    operator_stack.pop()

        if num_buffer:
            num_str = ''.join(num_buffer)
            try:
                num = float(num_str)
            except ValueError:
                raise ValueError("Invalid number format")
            operand_stack.append(num)

        while operator_stack:
            self.apply_operator(operand_stack, operator_stack)

        if operand_stack:
            return operand_stack[-1]
        else:
            return None