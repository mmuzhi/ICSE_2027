import re
from collections import deque

class ExpressionCalculator:
    def __init__(self):
        self.operat_priority = [0, 3, 2, 1, -1, 1, 0, 2]
    
    def calculate(self, expression: str) -> float:
        expression = self.transform(expression)
        self.prepare(expression)
        
        reversed_postfix_stack = deque(reversed(self.postfix_stack))
        result_stack = deque()
        
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
        
        result_str = '*'.join(result_stack)
        return float(result_str)
    
    def prepare(self, expression: str) -> None:
        self.postfix_stack = deque()
        op_stack = deque([','])
        current_index = 0
        count = 0
        
        for i, char in enumerate(expression):
            if char == ' ':
                continue
            if self.is_operator(char):
                if count > 0:
                    self.postfix_stack.append(expression[current_index:i])
                    count = 0
                while (char != '(' and op_stack[-1] != ',' and
                       self.compare(char, op_stack[-1])):
                    self.postfix_stack.append(op_stack.pop())
                op_stack.append(char)
                current_index = i + 1
            else:
                count += 1
                
        if count > 0:
            self.postfix_stack.append(expression[current_index:])
        
        while op_stack[-1] != ',':
            self.postfix_stack.append(op_stack.pop())
    
    def is_operator(self, token: str) -> bool:
        return token in "+-*/()%" and len(token) == 1
    
    def compare(self, current_op: str, peek_op: str) -> bool:
        if current_op == '%':
            current_op = '/'
        if peek_op == '%':
            peek_op = '/'
        
        try:
            cur_index = ord(current_op) - 40
            peek_index = ord(peek_op) - 40
            if cur_index < 0 or cur_index >= len(self.operat_priority) or peek_index < 0 or peek_index >= len(self.operat_priority):
                return False
            cur_prec = self.operat_priority[cur_index]
            peek_prec = self.operat_priority[peek_index]
        except:
            return False
        
        return peek_prec >= cur_prec
    
    def _calculate(self, first_value: str, second_value: str, current_op: str) -> float:
        f = float(first_value)
        s = float(second_value)
        if current_op == '+':
            return f + s
        elif current_op == '-':
            return f - s
        elif current_op == '*':
            return f * s
        elif current_op == '/':
            return f / s
        elif current_op == '%':
            return f % s
        else:
            raise ValueError(f"Unexpected operator: {current_op}")
    
    def transform(self, expression: str) -> str:
        expression = re.sub(r'\s+', '', expression)
        expression = re.sub(r'=$', '', expression)
        
        new_expr = []
        for i, char in enumerate(expression):
            if char == '-' and (i == 0 or i > 0 and expression[i-1] in '+-*/()Ee'):
                new_expr.append('~')
            else:
                new_expr.append(char)
        expr = ''.join(new_expr)
        
        if expr.startswith('~') and len(expr) > 1 and expr[1] == '(':
            expr = '0' + expr[1:]
            return expr
        return expr