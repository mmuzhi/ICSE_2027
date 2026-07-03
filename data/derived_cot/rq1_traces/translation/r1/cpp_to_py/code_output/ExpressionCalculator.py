import re
import math

class ExpressionCalculator:
    def __init__(self):
        self.operat_priority = [0, 3, 2, 1, -1, 1, 0, 2]
        self.postfix_stack = []

    def calculate(self, expression):
        transformed_expr = self.transform(expression)
        self.prepare(transformed_expr)
        
        result_stack = []
        for token in self.postfix_stack:
            if not self.is_operator(token):
                token = token.replace('~', '-')
                result_stack.append(token)
            else:
                operand2 = result_stack.pop()
                operand1 = result_stack.pop()
                num1 = float(operand1)
                num2 = float(operand2)
                result = self._calculate(num1, num2, token)
                result_stack.append(str(result))
        
        result_str = "*".join(result_stack)
        return float(result_str)

    def prepare(self, expression):
        op_stack = [',']
        arr = expression
        current_index = 0
        count = 0
        self.postfix_stack = []
        
        for i in range(len(arr)):
            current_op = arr[i]
            if self.is_operator(current_op):
                if count > 0:
                    operand = arr[current_index:current_index+count]
                    self.postfix_stack.append(operand)
                peek_op = op_stack[-1]
                if current_op == ')':
                    while op_stack[-1] != '(':
                        op = op_stack.pop()
                        self.postfix_stack.append(op)
                    op_stack.pop()
                else:
                    while current_op != '(' and peek_op != ',' and self.compare(current_op, peek_op):
                        op = op_stack.pop()
                        self.postfix_stack.append(op)
                        peek_op = op_stack[-1]
                    op_stack.append(current_op)
                count = 0
                current_index = i + 1
            else:
                count += 1
                
        if count > 0:
            operand = arr[current_index:current_index+count]
            self.postfix_stack.append(operand)
            
        while op_stack[-1] != ',':
            op = op_stack.pop()
            self.postfix_stack.append(op)

    def is_operator(self, s):
        operators = {"+", "-", "*", "/", "(", ")", "%"}
        return s in operators

    def compare(self, cur, peek):
        cur_op = '/' if cur == '%' else cur
        peek_op = '/' if peek == '%' else peek
        
        idx_peek = ord(peek_op) - 40
        idx_cur = ord(cur_op) - 40
        
        if idx_peek < 0 or idx_peek >= len(self.operat_priority):
            return False
        if idx_cur < 0 or idx_cur >= len(self.operat_priority):
            return False
            
        priority_peek = self.operat_priority[idx_peek]
        priority_cur = self.operat_priority[idx_cur]
        
        return priority_peek >= priority_cur

    def _calculate(self, first_value, second_value, current_op):
        if current_op == '+':
            return first_value + second_value
        if current_op == '-':
            return first_value - second_value
        if current_op == '*':
            return first_value * second_value
        if current_op == '/':
            return first_value / second_value
        if current_op == '%':
            return math.fmod(first_value, second_value)
        raise ValueError(f"Unexpected operator: {current_op}")

    def transform(self, expression):
        expr = re.sub(r'\s+', '', expression)
        expr = re.sub(r'=$', '', expr)
        
        expr_list = list(expr)
        for i in range(len(expr_list)):
            if expr_list[i] == '-':
                if i == 0:
                    expr_list[i] = '~'
                else:
                    prev_char = expr_list[i-1]
                    if prev_char in {'+', '-', '*', '/', '(', 'E', 'e'}:
                        expr_list[i] = '~'
        expr = ''.join(expr_list)
        
        if expr.startswith('~') and len(expr) > 1 and expr[1] == '(':
            expr = '-' + expr[1:]
            return "0" + expr
        else:
            return expr