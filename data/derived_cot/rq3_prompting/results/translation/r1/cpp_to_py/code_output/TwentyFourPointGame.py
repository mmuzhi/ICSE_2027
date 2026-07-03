import random
import time
import math
from typing import List, Dict, Tuple

class Calculator:
    def __init__(self):
        self.operators: Dict[str, callable] = {
            '+': lambda x, y: x + y,
            '-': lambda x, y: x - y,
            '*': lambda x, y: x * y,
            '/': lambda x, y: x / y,
            '^': lambda x, y: math.pow(x, y)
        }

    def precedence(self, op: str) -> int:
        if op in ('+', '-'):
            return 1
        if op in ('*', '/'):
            return 2
        if op == '^':
            return 3
        return 0

    def apply_operator(self, operand_stack: List[float], operator_stack: List[str]) -> Tuple[List[float], List[str]]:
        # Make copies to avoid mutating the original stacks (matching C++ pass-by-value semantics)
        operand_stack = operand_stack[:]
        operator_stack = operator_stack[:]

        op = operator_stack.pop()
        operand2 = operand_stack.pop()
        operand1 = operand_stack.pop()
        result = self.operators[op](operand1, operand2)
        operand_stack.append(result)
        return operand_stack, operator_stack

    def calculate(self, expression: str) -> float:
        if not expression:
            return 0.0

        operand_stack: List[float] = []
        operator_stack: List[str] = []
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
                        operand_stack, operator_stack = self.apply_operator(operand_stack, operator_stack)
                    operator_stack.append(ch)
                elif ch == '(':
                    operator_stack.append(ch)
                elif ch == ')':
                    while operator_stack and operator_stack[-1] != '(':
                        operand_stack, operator_stack = self.apply_operator(operand_stack, operator_stack)
                    operator_stack.pop()  # remove '('

        if num_buffer:
            operand_stack.append(float(num_buffer))

        while operator_stack:
            operand_stack, operator_stack = self.apply_operator(operand_stack, operator_stack)

        return operand_stack[-1] if operand_stack else 0.0


class TwentyFourPointGame:
    def __init__(self):
        self.nums: List[int] = []
        random.seed(time.time())

    def generate_cards(self):
        for _ in range(4):
            self.nums.append(random.randint(1, 9))

    def get_my_cards(self) -> List[int]:
        self.nums.clear()
        self.generate_cards()
        return self.nums

    def answer(self, expression: str) -> List[int]:
        if expression == "pass":
            return self.get_my_cards()

        # Count how many times each digit (that appears in self.nums) is used in expression
        statistic: Dict[str, int] = {}
        for ch in expression:
            if ch.isdigit() and int(ch) in self.nums:
                statistic[ch] = statistic.get(ch, 0) + 1

        nums_used = statistic.copy()

        # Check that each card appears exactly once in the expression
        for num in self.nums:
            key = str(num)
            if key in nums_used and nums_used[key] > 0:
                nums_used[key] -= 1
            else:
                return []  # card not used or used too many times

        # All entry counts must be zero (every digit was matched)
        if all(cnt == 0 for cnt in nums_used.values()):
            if self.evaluate_expression(expression):
                return [1]
            else:
                return []
        else:
            return []

    def evaluate_expression(self, expression: str) -> bool:
        try:
            # Check first and last characters (must be digit or '(' / ')')
            if not expression:
                return False
            first = expression[0]
            last = expression[-1]
            if not (first.isdigit() or first == '('):
                return False
            if not (last.isdigit() or last == ')'):
                return False

            calculator = Calculator()
            ans = calculator.calculate(expression)
            return abs(ans - 24.0) < 1e-9   # floating point equality
        except Exception:
            return False

    def set_nums(self, now: List[int]):
        self.nums = now