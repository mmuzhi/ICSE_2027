"""
C++ 签名提取和转换模块

使用正则表达式从 C++ 代码中提取和转换函数签名。
"""

import re
from dataclasses import dataclass, field
from typing import Dict, List, Set, Tuple, Optional


@dataclass
class CppMethodSignature:
    """C++ 方法签名信息"""
    name: str
    return_type: str
    params: str  # 参数列表字符串
    is_const: bool = False
    is_static: bool = False
    is_virtual: bool = False
    
    def __hash__(self):
        return hash(self.name)


@dataclass
class CppClassSignature:
    """C++ 类签名信息"""
    name: str
    methods: Dict[str, CppMethodSignature] = field(default_factory=dict)
    
    def add_method(self, method: CppMethodSignature):
        self.methods[method.name] = method


# 匹配类定义（获取类名和类体）
CLASS_PATTERN = re.compile(
    r'class\s+(\w+)\s*(?::\s*(?:public|private|protected)\s+\w+)?\s*\{',
    re.MULTILINE
)

# 匹配类内方法声明（只有声明）
# 例如: double fidelity_discount() const;
METHOD_DECL_PATTERN = re.compile(
    r'^\s*(static\s+)?(virtual\s+)?'  # static/virtual
    r'([\w:]+(?:\s*[*&])?)\s+'  # 返回类型
    r'(\w+)\s*'  # 方法名
    r'\(([^)]*)\)\s*'  # 参数列表
    r'(const)?\s*'  # const 修饰符
    r'(?:override\s*)?'  # override
    r';',  # 分号结尾
    re.MULTILINE
)

# 匹配类外方法定义
# 例如: double DiscountStrategy::fidelity_discount() const { ... }
METHOD_DEF_PATTERN = re.compile(
    r'([\w:]+(?:\s*[*&])?)\s+'  # 返回类型
    r'(\w+)::(\w+)\s*'  # 类名::方法名
    r'\(([^)]*)\)\s*'  # 参数列表
    r'(const)?\s*'  # const 修饰符
    r'\{',  # 左花括号
    re.MULTILINE
)

# 匹配类内方法定义（内联实现）
# 例如: double total() { return 0; }
INLINE_METHOD_PATTERN = re.compile(
    r'^\s*(static\s+)?(virtual\s+)?'  # static/virtual
    r'([\w:]+(?:\s*[*&])?)\s+'  # 返回类型
    r'(\w+)\s*'  # 方法名
    r'\(([^)]*)\)\s*'  # 参数列表
    r'(const)?\s*'  # const 修饰符
    r'(?:override\s*)?'  # override
    r'\{',  # 左花括号开始
    re.MULTILINE
)


def find_class_body(code: str, class_start: int) -> Tuple[str, str]:
    """
    找到类体内容（处理嵌套花括号）
    返回 (类名, 类体内容)
    """
    # 找到类名
    match = CLASS_PATTERN.search(code, class_start)
    if not match:
        return None, None
    
    class_name = match.group(1)
    brace_start = match.end() - 1  # 第一个 { 的位置
    
    # 计算匹配的花括号
    depth = 1
    i = brace_start + 1
    while i < len(code) and depth > 0:
        if code[i] == '{':
            depth += 1
        elif code[i] == '}':
            depth -= 1
        i += 1
    
    class_body = code[brace_start + 1:i - 1]
    return class_name, class_body


def extract_cpp_signatures(code: str) -> Dict[str, CppClassSignature]:
    """
    从 C++ 代码中提取类和方法签名
    
    支持:
    - 类外定义: double ClassName::method() { }
    - 类内定义（内联）: double method() { }
    - 类内声明: double method();
    
    Args:
        code: C++ 源代码字符串
        
    Returns:
        Dict[class_name, CppClassSignature]
    """
    classes: Dict[str, CppClassSignature] = {}
    
    # 1. 从类外定义中提取方法
    for match in METHOD_DEF_PATTERN.finditer(code):
        return_type = match.group(1).strip()
        class_name = match.group(2)
        method_name = match.group(3)
        params = match.group(4).strip()
        is_const = match.group(5) is not None
        
        if class_name not in classes:
            classes[class_name] = CppClassSignature(name=class_name)
        
        method_sig = CppMethodSignature(
            name=method_name,
            return_type=return_type,
            params=params,
            is_const=is_const
        )
        classes[class_name].add_method(method_sig)
    
    # 2. 从类内提取内联方法定义
    for class_match in CLASS_PATTERN.finditer(code):
        class_name, class_body = find_class_body(code, class_match.start())
        if not class_body:
            continue
        
        if class_name not in classes:
            classes[class_name] = CppClassSignature(name=class_name)
        
        # 查找内联方法定义
        for match in INLINE_METHOD_PATTERN.finditer(class_body):
            is_static = match.group(1) is not None
            return_type = match.group(3).strip()
            method_name = match.group(4)
            params = match.group(5).strip()
            is_const = match.group(6) is not None
            
            # 跳过构造函数（返回类型为空或与类名相同的情况已被正则排除）
            # 跳过已存在的方法
            if method_name not in classes[class_name].methods:
                method_sig = CppMethodSignature(
                    name=method_name,
                    return_type=return_type,
                    params=params,
                    is_const=is_const,
                    is_static=is_static
                )
                classes[class_name].add_method(method_sig)
    
    return classes


def extract_cpp_signatures_from_file(filepath: str) -> Dict[str, CppClassSignature]:
    """从 C++ 文件中提取签名"""
    with open(filepath, 'r', encoding='utf-8') as f:
        code = f.read()
    return extract_cpp_signatures(code)


def transform_cpp_code(code: str, class_mappings: Dict[str, Dict[str, str]]) -> str:
    """
    转换 C++ 代码中的方法签名
    
    Args:
        code: 原始 C++ 代码
        class_mappings: 类方法映射 {class_name: {source_method: target_method}}
        
    Returns:
        转换后的代码
    """
    result = code
    
    for class_name, method_map in class_mappings.items():
        for src_name, tgt_name in method_map.items():
            if src_name == tgt_name:
                continue
            
            # 1. 替换类外定义: ClassName::old_method -> ClassName::new_method
            pattern = rf'(\b{class_name}::){src_name}(\s*\()'
            result = re.sub(pattern, rf'\g<1>{tgt_name}\g<2>', result)
            
            # 2. 替换类内声明（分号结尾）
            # 例如: double old_method() const;
            pattern = rf'(\s+){src_name}(\s*\([^)]*\)\s*(?:const)?\s*;)'
            result = re.sub(pattern, rf'\g<1>{tgt_name}\g<2>', result)
            
            # 3. 替换类内内联定义（花括号开始）
            # 例如: static double old_method() { 或 double old_method() const {
            pattern = rf'(\s+){src_name}(\s*\([^)]*\)\s*(?:const)?\s*\{{)'
            result = re.sub(pattern, rf'\g<1>{tgt_name}\g<2>', result)
            
            # 4. 替换方法调用: this->old_method()
            pattern = rf'(this\s*->\s*){src_name}(\s*\()'
            result = re.sub(pattern, rf'\g<1>{tgt_name}\g<2>', result)
            
            # 5. 普通方法调用: obj.method()
            pattern = rf'(\.\s*){src_name}(\s*\()'
            result = re.sub(pattern, rf'\g<1>{tgt_name}\g<2>', result)
    
    return result


if __name__ == "__main__":
    # 测试代码
    test_code = '''
class DiscountStrategy {
public:
    double fidelity_discount() const;
    double bulk_item_discount() const;
};

double DiscountStrategy::fidelity_discount() const {
    return this->total() * 0.05;
}

double DiscountStrategy::bulk_item_discount() const {
    return 0;
}
'''
    
    # 提取签名
    sigs = extract_cpp_signatures(test_code)
    print("提取的签名:")
    for class_name, class_sig in sigs.items():
        print(f"类 {class_name}:")
        for method_name in class_sig.methods:
            print(f"  - {method_name}")
    
    # 转换测试
    mappings = {
        "DiscountStrategy": {
            "fidelity_discount": "FidelityPromo",
            "bulk_item_discount": "BulkItemPromo"
        }
    }
    
    result = transform_cpp_code(test_code, mappings)
    print("\n转换后的代码:")
    print(result)
