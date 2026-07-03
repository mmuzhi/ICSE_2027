class ExpressionCalculator:
    def __init__(self):
        self.postfixStack = []

    def calculate(self, expression):
        transformed = self.transform(expression)
        self.prepare(transformed)
        return self.evaluatePostfix()

    def prepare(self, expression):
        self.postfixStack.clear()
        operatorStack = []
        i = 0
        n = len(expression)
        while i < n:
            ch = expression[i]
            if ch.isdigit() or ch == '.':
                num = ''
                while i < n and (expression[i].isdigit() or expression[i] == '.'):
                    num += expression[i]
                    i += 1
                i -= 1
                self.postfixStack.append(num)
            elif ch == '(':
                operatorStack.append(ch)
            elif ch == ')':
                while operatorStack and operatorStack[-1] != '(':
                    self.postfixStack.append(operatorStack.pop())
                operatorStack.pop()
            elif self.isOperator(ch):
                while operatorStack and self.isOperator(operatorStack[-1]) and not self.compare(operatorStack[-1], ch):
                    self.postfixStack.append(operatorStack.pop())
                operatorStack.append(ch)
            i += 1
        while operatorStack:
            self.postfixStack.append(operatorStack.pop())

    def isOperator(self, ch):
        return ch in '+-*/%'

    def compare(self, op1, op2):
        cur_op = '/' if op1 == '%' else op1
        peek_op = '/' if op2 == '%' else op2
        priority = [0, 3, 2, 1, -1, 1, 0, 2]  # indices for '(' (40) to '/' (47)
        return priority[ord(peek_op) - 40] >= priority[ord(cur_op) - 40]

    def evaluatePostfix(self):
        stack = []
        for token in self.postfixStack:
            if len(token) == 1 and self.isOperator(token[0]):
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
            raise ValueError("Unsupported operator: " + operator)

    def transform(self, expression):
        expression = expression.replace(" ", "")
        expression = expression.replace("-", "~")
        if len(expression) > 1 and expression[0] == '~' and expression[1] == '(':
            # convert "~( ... )" to "0-( ... )"
            expression = '0' + '-' + expression[1:]
        return expression