import random
import math


class TwentyFourPointGame:
    def __init__(self):
        self.nums = []
        random.seed()

    def _generate_cards(self):
        self.nums = [random.randint(1, 9) for _ in range(4)]
        assert len(self.nums) == 4

    def get_my_cards(self):
        self.nums.clear()
        self._generate_cards()
        return self.nums

    def answer(self, expression):
        if expression == "pass":
            return self.get_my_cards()

        statistic = {}
        for c in expression:
            if c.isdigit() and int(c) in self.nums:
                statistic[c] = statistic.get(c, 0) + 1

        nums_used = dict(statistic)

        for num in self.nums:
            key = chr(ord('0') + num)
            if key in nums_used and nums_used[key] > 0:
                nums_used[key] -= 1
            else:
                return []

        if all(v == 0 for v in nums_used.values()):
            if self.evaluate_expression(expression):
                return [1]
            else:
                return []
        else:
            return []

    def evaluate_expression(self, expression):
        try:
            if expression[0] < '0' or expression[0] > '9':
                if expression[0] != '(':
                    raise ValueError
            kkk = len(expression) - 1
            if expression[kkk] < '0' or expression[kkk] > '9':
                if expression[kkk] != ')':
                    raise ValueError
            calculator = Calculator()
            ans = calculator.calculate(expression)
            if ans == 24.0:
                return True
            else:
                return False
        except:
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
            '^': lambda x, y: math.pow(x, y),
        }

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
                if num_buffer:
                    operand_stack.append(float(num_buffer))
                    num_buffer = ""

                if ch in ('+', '-', '*', '/', '^'):
                    while (operator_stack and operator_stack[-1] != '(' and
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
            operand_stack.append(float(num_buffer))

        while operator_stack:
            self.apply_operator(operand_stack, operator_stack)

        return operand_stack[-1] if operand_stack else 0.0

    def precedence(self, op):
        if op in ('+', '-'):
            return 1
        elif op in ('*', '/'):
            return 2
        elif op == '^':
            return 3
        else:
            return 0

    def apply_operator(self, operand_stack, operator_stack):
        op = operator_stack.pop()
        operand2 = operand_stack.pop()
        operand1 = operand_stack.pop()
        result = self.operators[op](operand1, operand2)
        operand_stack.append(result)