"""
代码转换模块

使用 AST 将翻译后代码的函数签名转换为目标签名。
"""

import ast
from typing import Dict, List, Set


class SignatureTransformer(ast.NodeTransformer):
    """
    AST 转换器，将方法名从源签名转换为目标签名
    """
    
    def __init__(self, class_mappings: Dict[str, Dict[str, str]]):
        """
        Args:
            class_mappings: 类方法映射 {class_name: {source_method: target_method}}
        """
        super().__init__()
        self.class_mappings = class_mappings
        # 使用栈结构处理嵌套类
        self._class_stack: List[str] = []
        self._renames_stack: List[Dict[str, str]] = []
    
    @property
    def _current_class(self) -> str:
        return self._class_stack[-1] if self._class_stack else None
    
    @property
    def _method_renames(self) -> Dict[str, str]:
        return self._renames_stack[-1] if self._renames_stack else {}
    
    def visit_ClassDef(self, node: ast.ClassDef) -> ast.ClassDef:
        """处理类定义，支持嵌套类"""
        # 入栈
        self._class_stack.append(node.name)
        self._renames_stack.append(self.class_mappings.get(node.name, {}))
        
        # 遍历子节点
        self.generic_visit(node)
        
        # 出栈
        self._class_stack.pop()
        self._renames_stack.pop()
        return node
    
    def visit_FunctionDef(self, node: ast.FunctionDef) -> ast.FunctionDef:
        """处理函数定义，重命名方法"""
        if self._current_class and node.name in self._method_renames:
            new_name = self._method_renames[node.name]
            if new_name != node.name:  # 只有不同时才重命名
                node.name = new_name
        
        # 遍历函数体中的调用
        self.generic_visit(node)
        return node
    
    def visit_AsyncFunctionDef(self, node: ast.AsyncFunctionDef) -> ast.AsyncFunctionDef:
        """处理异步函数定义"""
        if self._current_class and node.name in self._method_renames:
            new_name = self._method_renames[node.name]
            if new_name != node.name:
                node.name = new_name
        
        self.generic_visit(node)
        return node
    
    def visit_Call(self, node: ast.Call) -> ast.Call:
        """处理函数调用，重命名内部方法调用"""
        # 处理 self.method() 形式的调用
        if isinstance(node.func, ast.Attribute):
            if isinstance(node.func.value, ast.Name) and node.func.value.id == 'self':
                if node.func.attr in self._method_renames:
                    new_name = self._method_renames[node.func.attr]
                    if new_name != node.func.attr:
                        node.func.attr = new_name
        
        self.generic_visit(node)
        return node


def transform_code(code: str, class_mappings: Dict[str, Dict[str, str]]) -> str:
    """
    转换代码中的方法签名
    
    Args:
        code: 原始 Python 代码
        class_mappings: 类方法映射 {class_name: {source_method: target_method}}
        
    Returns:
        转换后的代码
    """
    try:
        tree = ast.parse(code)
    except SyntaxError as e:
        print(f"语法错误，无法解析代码: {e}")
        return code
    
    # 过滤掉不需要转换的映射 (源和目标相同)
    filtered_mappings = {}
    for class_name, method_map in class_mappings.items():
        filtered_map = {src: tgt for src, tgt in method_map.items() if src != tgt}
        if filtered_map:
            filtered_mappings[class_name] = filtered_map
    
    if not filtered_mappings:
        return code  # 无需转换
    
    transformer = SignatureTransformer(filtered_mappings)
    new_tree = transformer.visit(tree)
    
    # 修复 AST 位置信息
    ast.fix_missing_locations(new_tree)
    
    # 使用 ast.unparse 生成代码 (Python 3.9+)
    try:
        return ast.unparse(new_tree)
    except AttributeError:
        # Python < 3.9，使用 astor 或返回原始代码
        try:
            import astor
            return astor.to_source(new_tree)
        except ImportError:
            print("警告: Python < 3.9 需要安装 astor 库来生成代码")
            return code


if __name__ == "__main__":
    # 测试代码
    test_code = '''
class CamelCaseMap:
    def __init__(self):
        self.data = {}
    
    def set_item(self, key, value):
        self.data[key] = value
    
    def get_item(self, key):
        return self.data[key]
    
    def del_item(self, key):
        del self.data[key]
    
    def len(self):
        return len(self.data)
    
    def test_internal_call(self):
        self.set_item("a", 1)
        return self.get_item("a")
'''
    
    mappings = {
        "CamelCaseMap": {
            "set_item": "__setitem__",
            "get_item": "__getitem__",
            "del_item": "__delitem__",
            "len": "__len__"
        }
    }
    
    result = transform_code(test_code, mappings)
    print("转换后的代码:")
    print(result)
