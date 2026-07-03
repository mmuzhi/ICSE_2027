import collections
import re
import math

class ExpressionCalculator:
    def __init__(self):
        # Priority mapping: same as C++ vector {0,3,2,1,-1,1,0,2}
        # ordered by ASCII codes: '('=40, ')'=41, '*'=42, '+'=43, ','=44, '-'=45, '.'=46, '/'=47
        self.operat_priority = {
            '(': 0,
            ')': 3,
            '*': 2,
            '+': 1,
            ',': -1,
            '-': 1,
            '.': 0,
            '/': 2
        }
        self.postfix_stack = collections.deque()

    def calculate(self, expression):
        self.prepare(self.transform(expression))

        result_stack = collections.deque()
        # process postfix from left to right (original order)
        while self.postfix_stack:
            current_op = self.postfix_stack.popleft()
            if not self.is_operator(current_op):
                current_op = current_op.replace('~', '-')
                result_stack.append(current_op)
            else:
                second_value = result_stack.pop()
                first_value = result_stack.pop()
                first_value = first_value.replace('~', '-')
                second_value = second_value.replace('~', '-')
                temp_result = self._calculate(first_value, second_value, current_op)
                result_stack.append(str(temp_result))

        # Build result exactly as C++: append each value + "*", then remove trailing '*', then convert to float
        result_str = ""
        for val in result_stack:
            result_str += val + "*"
        if result_str:
            result_str = result_str[:-1]
        return float(result_str)

    def prepare(self, expression):
        op_stack = collections.deque([","])  # sentinel
        arr = expression
        current_index = 0
        count = 0
        self.postfix_stack.clear()

        i = 0
        while i < len(arr):
            current_op = arr[i]
            if self.is_operator(current_op):
                if count > 0:
                    self.postfix_stack.append(arr[current_index:current_index + count])

                if current_op == ")":
                    while op_stack and op_stack[-1] != "(":
                        self.postfix_stack.append(op_stack.pop())
                    if op_stack and op_stack[-1] == "(":
                        op_stack.pop()  # remove '('
                else:
                    peek_op = op_stack[-1] if op_stack else None
                    while current_op != "(" and peek_op != "," and self.compare(current_op, peek_op):
                        self.postfix_stack.append(op_stack.pop())
                        peek_op = op_stack[-1] if op_stack else None
                    op_stack.append(current_op)

                count = 0
                current_index = i + 1
            else:
                count += 1
            i += 1

        # After the loop, handle remaining numeric part
        if count > 1 or (count == 1 and not self.is_operator(arr[current_index:current_index + count])):
            self.postfix_stack.append(arr[current_index:current_index + count])

        # Move remaining operators from stack to postfix (except sentinel)
        while op_stack and op_stack[-1] != ",":
            self.postfix_stack.append(op_stack.pop())

    @staticmethod
    def is_operator(c):
        return c in {"+", "-", "*", "/", "(", ")", "%"}

    def compare(self, cur, peek):
        # Treat '%' as '/' for priority comparison
        cur_op = "/" if cur == "%" else cur
        peek_op = "/" if peek == "%" else peek
        prio_peek = self.operat_priority.get(peek_op, -100)
        prio_cur = self.operat_priority.get(cur_op, -100)
        return prio_peek >= prio_cur

    @staticmethod
    def _calculate(first_value, second_value, current_op):
        f = float(first_value)
        s = float(second_value)

        if current_op == "+":
            return f + s
        elif current_op == "-":
            return f - s
        elif current_op == "*":
            return f * s
        elif current_op == "/":
            # Match C++ behavior for division by zero: returns inf/ -inf / nan
            if s == 0.0:
                return f * float('inf')
            return f / s
        elif current_op == "%":
            # Use math.fmod to match C++ fmod behavior (including division by zero -> nan)
            return math.fmod(f, s)
        else:
            raise ValueError("Unexpected operator: " + current_op)

    @staticmethod
    def transform(expression):
        # Remove whitespace and trailing '='
        expr = re.sub(r'\s+', '', expression)
        expr = re.sub(r'=$', '', expr)

        # Replace unary minus with '~'
        chars = []
        for i, ch in enumerate(expr):
            if ch == '-':
                if i == 0:
                    chars.append('~')
                else:
                    prev = expr[i - 1]
                    if prev in {'+', '-', '*', '/', '(', 'E', 'e'}:
                        chars.append('~')
                    else:
                        chars.append('-')
            else:
                chars.append(ch)
        expr = ''.join(chars)

        # Special case: expression starts with "~(" -> convert to "0-("
        if len(expr) > 1 and expr[0] == '~' and expr[1] == '(':
            # Change '~' to '-' and prepend "0"
            expr = '-' + expr[1:]
            return "0" + expr
        else:
            return expr