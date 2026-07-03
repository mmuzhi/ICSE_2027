class Calculator:
    def __init__(self):
        self.operators = {
            '+': lambda x, y: x + y,
            '-': lambda x, y: x - y,
            '*': lambda x, y: x * y,
            '/': lambda x, y: x / y,
            '^': lambda x, y: x ** y
        }

    def _precedence(self, operator):
        if operator in ('+', '-'):
            return 1
        elif operator in ('*', '/'):
            return 2
        elif operator == '^':
            return 3
        else:
            return 0

    def _apply_operator(self, operand_stack, operator_stack):
        operator = operator_stack.pop()
        operand2 = operand_stack.pop()
        operand1 = operand_stack.pop()
        result = self.operators[operator](operand1, operand2)
        operand_stack.append(result)

    def calculate(self, expression):
        operand_stack = []
        operator_stack = []
        num_buffer = []

        for ch in expression:
            if ch.isdigit() or ch == '.':
                num_buffer.append(ch)
            else:
                if num_buffer:
                    operand_stack.append(float(''.join(num_buffer)))
                    num_buffer = []

                if ch in self.operators:
                    while (operator_stack and operator_stack[-1] != '(' and
                           self._precedence(operator_stack[-1]) >= self._precedence(ch)):
                        self._apply_operator(operand_stack, operator_stack)
                    operator_stack.append(ch)
                elif ch == '(':
                    operator_stack.append(ch)
                elif ch == ')':
                    while operator_stack and operator_stack[-1] != '(':
                        self._apply_operator(operand_stack, operator_stack)
                    if operator_stack:
                        operator_stack.pop()

        if num_buffer:
            operand_stack.append(float(''.join(num_buffer)))

        while operator_stack:
            self._apply_operator(operand_stack, operator_stack)

        return operand_stack[-1] if operand_stack else None


if __name__ == '__main__':
    calc = Calculator()
    print(calc.calculate("1+2-3"))