import re
from collections import deque

class ExpressionCalculator:
    def __init__(self):
        self.priority = {
            '+': 3,
            '-': 5,
            '*': 2,
            '/': 7,
            '(': 0,
            ')': 1,
            '%': 7
        }

    def is_operator(self, c):
        return c in ['+', '-', '*', '/', '(', ')', '%']

    def compare(self, cur, peek):
        cur_op = cur if cur != '%' else '/'
        peek_op = peek if peek != '%' else '/'
        return self.priority[peek_op] >= self.priority[cur_op]

    def _calculate(self, first_value, second_value, current_op):
        f = float(first_value)
        s = float(second_value)
        if current_op == '+': return f + s
        if current_op == '-': return f - s
        if current_op == '*': return f * s
        if current_op == '/': return f / s
        if current_op == '%': return f % s
        raise ValueError(f"Unexpected operator: {current_op}")

    def transform(self, expression):
        expr = re.sub(r'\s+', '', expression)
        expr = re.sub(r'=$', '', expr)
        new_expr = list(expr)
        for i in range(len(new_expr)):
            if new_expr[i] == '-':
                if i == 0:
                    new_expr[i] = '~'
                else:
                    prev_c = new_expr[i-1]
                    if prev_c in ['+', '-', '*', '/', '(', 'e', 'E']:
                        new_expr[i] = '~'
        if new_expr and new_expr[0] == '~' and len(new_expr) > 1 and new_expr[1] == '(':
            new_expr[0] = '-'
            return '0' + ''.join(new_expr)
        else:
            return ''.join(new_expr)

    def prepare(self, expression):
        op_stack = deque([','])
        postfix_stack = []
        current_index = 0
        count = 0
        n = len(expression)
        for i in range(n):
            if self.is_operator(expression[i]):
                if count > 0:
                    token = expression[current_index:i]
                    postfix_stack.append(token)
                if expression[i] == ')':
                    while op_stack[-1] != '(':
                        postfix_stack.append(op_stack.pop())
                    op_stack.pop()
                else:
                    while (expression[i] != '(' and op_stack[-1] != ',' and self.compare(expression[i], op_stack[-1])):
                        postfix_stack.append(op_stack.pop())
                    op_stack.append(expression[i])
                count = 0
                current_index = i + 1
            else:
                count += 1
        if count > 0:
            token = expression[current_index:]
            if count > 1 or (count == 1 and not self.is_operator(token)):
                postfix_stack.append(token)
        while op_stack[-1] != ',':
            postfix_stack.append(op_stack.pop())

    def calculate(self, expression):
        self.prepare(self.transform(expression))
        result_stack = []
        reversed_postfix_stack = list(self.postfix_stack[::-1])
        while reversed_postfix_stack:
            current_op = reversed_postfix_stack.pop()
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
        return float(result_stack[0])