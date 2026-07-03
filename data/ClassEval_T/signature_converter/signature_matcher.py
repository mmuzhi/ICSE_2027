"""
签名匹配模块

建立翻译后代码签名到目标签名的映射关系。
"""

import re
from typing import Dict, List, Tuple, Set
from difflib import SequenceMatcher

from .signature_extractor import ClassSignature, MethodSignature


def extract_keywords(name: str) -> Set[str]:
    """
    从方法名中提取关键词
    支持 snake_case, camelCase, PascalCase
    """
    # 移除开头的下划线
    name = name.lstrip('_')
    
    # 按下划线分割 (snake_case)
    parts = name.split('_')
    
    # 按大写字母分割 (camelCase, PascalCase)
    keywords = set()
    for part in parts:
        # 使用正则按大写字母分割
        sub_parts = re.findall(r'[A-Z]?[a-z]+|[A-Z]+(?=[A-Z][a-z]|\d|\W|$)|\d+', part)
        if sub_parts:
            keywords.update(word.lower() for word in sub_parts)
        else:
            keywords.add(part.lower())
    
    # 移除过短的关键词
    keywords = {k for k in keywords if len(k) > 1}
    
    return keywords


def normalize_method_name(name: str) -> str:
    """
    标准化方法名，用于比较
    移除下划线，转为小写
    """
    return name.replace('_', '').lower()


def calculate_keyword_similarity(name1: str, name2: str) -> float:
    """
    计算两个方法名的关键词相似度
    
    Args:
        name1: 第一个方法名
        name2: 第二个方法名
        
    Returns:
        相似度分数 (0.0 - 1.0)
    """
    keywords1 = extract_keywords(name1)
    keywords2 = extract_keywords(name2)
    
    if not keywords1 or not keywords2:
        return 0.0
    
    # 计算交集
    common = keywords1 & keywords2
    
    # Jaccard 相似度
    union = keywords1 | keywords2
    if not union:
        return 0.0
    
    jaccard = len(common) / len(union)
    
    # 如果有重要关键词匹配，给予额外加分
    # 关键词越长越重要
    bonus = 0.0
    for keyword in common:
        if len(keyword) >= 5:  # 较长的关键词更重要
            bonus += 0.1
        elif len(keyword) >= 3:
            bonus += 0.05
    
    return min(1.0, jaccard + bonus)


def calculate_name_similarity(name1: str, name2: str) -> float:
    """
    计算两个方法名的综合相似度
    
    Args:
        name1: 第一个方法名
        name2: 第二个方法名
        
    Returns:
        相似度分数 (0.0 - 1.0)
    """
    # 标准化后比较
    norm1 = normalize_method_name(name1)
    norm2 = normalize_method_name(name2)
    
    # 完全匹配
    if norm1 == norm2:
        return 1.0
    
    # 字符序列相似度
    seq_sim = SequenceMatcher(None, norm1, norm2).ratio()
    
    # 关键词相似度
    keyword_sim = calculate_keyword_similarity(name1, name2)
    
    # 取两者中的较大值，因为两种方法各有优势
    return max(seq_sim, keyword_sim)


def calculate_param_similarity(params1: List[str], params2: List[str]) -> float:
    """
    计算两个参数列表的相似度
    
    Args:
        params1: 第一个参数列表
        params2: 第二个参数列表
        
    Returns:
        相似度分数 (0.0 - 1.0)
    """
    # 参数数量不同，但如果差距不大也可以接受
    # 因为 staticmethod 和普通方法的参数数量可能不同
    len1, len2 = len(params1), len(params2)
    
    if len1 == len2:
        if len1 == 0:
            return 1.0
        # 比较参数名
        total_sim = 0.0
        for p1, p2 in zip(params1, params2):
            total_sim += SequenceMatcher(None, p1.lower(), p2.lower()).ratio()
        return total_sim / len1
    else:
        # 参数数量差距越大，相似度越低
        # 但保持一个基准值，不要因为参数差异就完全否定匹配
        max_len = max(len1, len2, 1)
        min_len = min(len1, len2)
        return 0.3 + (min_len / max_len) * 0.4


def match_methods(
    source_methods: Dict[str, MethodSignature],
    target_methods: Dict[str, MethodSignature],
    threshold: float = 0.5
) -> Dict[str, str]:
    """
    匹配源方法到目标方法
    
    Args:
        source_methods: 翻译后代码的方法签名
        target_methods: Python 原生代码的方法签名 (ground truth)
        threshold: 匹配阈值
        
    Returns:
        映射字典 {source_method_name: target_method_name}
    """
    mapping = {}
    used_targets = set()
    
    # 计算所有方法对的相似度
    scores: List[Tuple[str, str, float]] = []
    
    for src_name, src_sig in source_methods.items():
        for tgt_name, tgt_sig in target_methods.items():
            # 完全相同的名字优先匹配
            if src_name == tgt_name:
                scores.append((src_name, tgt_name, 2.0))  # 高优先级
                continue
            
            # 计算相似度
            name_sim = calculate_name_similarity(src_name, tgt_name)
            param_sim = calculate_param_similarity(src_sig.params, tgt_sig.params)
            
            # 综合相似度 (名称权重更高)
            total_sim = name_sim * 0.7 + param_sim * 0.3
            
            if total_sim >= threshold:
                scores.append((src_name, tgt_name, total_sim))
    
    # 按相似度降序排序
    scores.sort(key=lambda x: x[2], reverse=True)
    
    # 贪婪匹配
    used_sources = set()
    for src_name, tgt_name, score in scores:
        if src_name not in used_sources and tgt_name not in used_targets:
            mapping[src_name] = tgt_name
            used_sources.add(src_name)
            used_targets.add(tgt_name)
    
    return mapping


def match_classes(
    source_classes: Dict[str, ClassSignature],
    target_classes: Dict[str, ClassSignature],
    threshold: float = 0.5
) -> Dict[str, Dict[str, str]]:
    """
    匹配源类的方法到目标类的方法
    
    Args:
        source_classes: 翻译后代码的类签名
        target_classes: Python 原生代码的类签名
        threshold: 匹配阈值
        
    Returns:
        映射字典 {class_name: {source_method_name: target_method_name}}
    """
    result = {}
    
    for class_name, source_class in source_classes.items():
        # 查找对应的目标类
        target_class = None
        
        # 首先尝试精确匹配类名
        if class_name in target_classes:
            target_class = target_classes[class_name]
        else:
            # 尝试模糊匹配类名
            for tgt_name, tgt_class in target_classes.items():
                if normalize_method_name(class_name) == normalize_method_name(tgt_name):
                    target_class = tgt_class
                    break
        
        if target_class is None:
            continue
        
        # 匹配方法
        method_mapping = match_methods(
            source_class.methods,
            target_class.methods,
            threshold
        )
        
        if method_mapping:
            result[class_name] = method_mapping
    
    return result


def create_signature_mapping(
    translated_code: str,
    target_code: str,
    threshold: float = 0.5
) -> Dict[str, Dict[str, str]]:
    """
    创建翻译后代码到目标代码的签名映射
    
    Args:
        translated_code: 翻译后的 Python 代码
        target_code: Python 原生代码 (ground truth)
        threshold: 匹配阈值
        
    Returns:
        映射字典 {class_name: {source_method_name: target_method_name}}
    """
    from .signature_extractor import extract_signatures
    
    source_classes = extract_signatures(translated_code)
    target_classes = extract_signatures(target_code)
    
    return match_classes(source_classes, target_classes, threshold)


if __name__ == "__main__":
    # 测试代码
    translated = '''
class CamelCaseMap:
    def set_item(self, key, value):
        pass
    def get_item(self, key):
        pass
    def del_item(self, key):
        pass
    def len(self):
        pass
'''
    
    target = '''
class CamelCaseMap:
    def __setitem__(self, key, value):
        pass
    def __getitem__(self, key):
        pass
    def __delitem__(self, key):
        pass
    def __len__(self):
        pass
'''
    
    mapping = create_signature_mapping(translated, target)
    print("签名映射:")
    for class_name, method_map in mapping.items():
        print(f"类 {class_name}:")
        for src, tgt in method_map.items():
            print(f"  {src} -> {tgt}")
