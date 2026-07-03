"""
签名提取模块

使用 Python AST 从源代码中提取类和方法的签名信息。
"""

import ast
from dataclasses import dataclass, field
from typing import Dict, List, Optional


@dataclass
class MethodSignature:
    """方法签名信息"""
    name: str
    params: List[str]  # 参数名列表 (不含 self)
    is_static: bool = False
    is_classmethod: bool = False
    
    def __hash__(self):
        return hash(self.name)


@dataclass
class ClassSignature:
    """类签名信息"""
    name: str
    methods: Dict[str, MethodSignature] = field(default_factory=dict)
    
    def add_method(self, method: MethodSignature):
        self.methods[method.name] = method


class SignatureExtractor(ast.NodeVisitor):
    """从 Python 代码中提取类和方法签名"""
    
    def __init__(self):
        self.classes: Dict[str, ClassSignature] = {}
        self._current_class: Optional[ClassSignature] = None
    
    def extract(self, code: str) -> Dict[str, ClassSignature]:
        """
        从代码中提取所有类的签名信息
        
        Args:
            code: Python 源代码字符串
            
        Returns:
            Dict[class_name, ClassSignature]
        """
        try:
            tree = ast.parse(code)
            self.visit(tree)
        except SyntaxError as e:
            print(f"语法错误: {e}")
        return self.classes
    
    def visit_ClassDef(self, node: ast.ClassDef):
        """访问类定义"""
        class_sig = ClassSignature(name=node.name)
        self._current_class = class_sig
        
        # 遍历类体中的方法
        for item in node.body:
            if isinstance(item, ast.FunctionDef) or isinstance(item, ast.AsyncFunctionDef):
                method_sig = self._extract_method_signature(item)
                class_sig.add_method(method_sig)
        
        self.classes[node.name] = class_sig
        self._current_class = None
        
        # 不继续遍历嵌套类
        return None
    
    def _extract_method_signature(self, node: ast.FunctionDef) -> MethodSignature:
        """提取方法签名"""
        # 检查装饰器
        is_static = False
        is_classmethod = False
        for decorator in node.decorator_list:
            if isinstance(decorator, ast.Name):
                if decorator.id == 'staticmethod':
                    is_static = True
                elif decorator.id == 'classmethod':
                    is_classmethod = True
        
        # 提取参数 (排除 self/cls)
        params = []
        args = node.args
        
        for arg in args.args:
            param_name = arg.arg
            if param_name not in ('self', 'cls'):
                params.append(param_name)
        
        return MethodSignature(
            name=node.name,
            params=params,
            is_static=is_static,
            is_classmethod=is_classmethod
        )


def extract_signatures(code: str) -> Dict[str, ClassSignature]:
    """
    从 Python 代码中提取类和方法签名
    
    Args:
        code: Python 源代码字符串
        
    Returns:
        Dict[class_name, ClassSignature]
    """
    extractor = SignatureExtractor()
    return extractor.extract(code)


def extract_signatures_from_file(filepath: str) -> Dict[str, ClassSignature]:
    """
    从 Python 文件中提取类和方法签名
    
    Args:
        filepath: Python 文件路径
        
    Returns:
        Dict[class_name, ClassSignature]
    """
    with open(filepath, 'r', encoding='utf-8') as f:
        code = f.read()
    return extract_signatures(code)


if __name__ == "__main__":
    # 测试代码
    test_code = '''
class BankAccount:
    def __init__(self, balance=0):
        self.balance = balance
    
    def deposit(self, amount):
        self.balance += amount
    
    def withdraw(self, amount):
        self.balance -= amount
    
    @staticmethod
    def validate_amount(amount):
        return amount > 0
'''
    
    signatures = extract_signatures(test_code)
    for class_name, class_sig in signatures.items():
        print(f"类: {class_name}")
        for method_name, method_sig in class_sig.methods.items():
            print(f"  方法: {method_name}, 参数: {method_sig.params}, static: {method_sig.is_static}")
