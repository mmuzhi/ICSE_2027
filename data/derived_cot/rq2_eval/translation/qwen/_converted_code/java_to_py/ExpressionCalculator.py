class ExpressionCalculator:
    def __init__(self):
        self.postfix_stack = []

    def calculate(self, expression):
        transformed_expression = self.transform(expression)
        self.prepare(transformed_expression)
        return self.evaluate_postfix()

    def prepare(self, expression):
        self.postfix_stack.clear()
        operator_stack = []
        i = 0
        n = len(expression)
        while i < n:
            c = expression[i]
            if c.isdigit() or c == '.':
                j = i
                while j < n and (expression[j].isdigit() or expression[j] == '.'):
                    j += 1
                num_str = expression[i:j]
                self.postfix_stack.append(num_str)
                i = j
            elif c == '(':
                operator_stack.append(c)
                i += 1
            elif c == ')':
                while operator_stack and operator_stack[-1] != '(':
                    self.postfix_stack.append(operator_stack.pop())
                if operator_stack and operator_stack[-1] == '(':
                    operator_stack.pop()
                i += 1
            elif self.is_operator(c):
                while operator_stack and operator_stack[-1] != '(' and self.is_operator(operator_stack[-1]) and not self.compare(operator_stack[-1], c):
                    self.postfix_stack.append(operator_stack.pop())
                operator_stack.append(c)
                i += 1
            else:
                i += 1
        while operator_stack:
            self.postfix_stack.append(operator_stack.pop())

    def is_operator(self, c):
        return c in '+-*/%'

    def compare(self, op1, op2):
        if op1 == '%':
            op1 = '/'
        if op2 == '%':
            op2 = '/'
        precedence = {
            '+': 1,
            '-': 1,
            '*': 2,
            '/': 2,
            '%': 2
        }
        return precedence[op2] >= precedence[op1]

    def evaluate_postfix(self):
        stack = []
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
            expression = expression[0].replace('~', '-') + expression[1:]
            return "0" + expression
        else:
            return expression