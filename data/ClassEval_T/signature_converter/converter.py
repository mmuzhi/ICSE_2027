"""
签名转换器主入口

整合签名提取、匹配和代码转换功能，提供统一的 API 和命令行接口。
"""

import argparse
import os
from pathlib import Path
from typing import Dict, Optional, Tuple

from .signature_extractor import extract_signatures, extract_signatures_from_file
from .signature_matcher import create_signature_mapping, match_classes
from .code_transformer import transform_code


def convert_code(
    translated_code: str,
    target_code: str,
    threshold: float = 0.5
) -> Tuple[str, Dict[str, Dict[str, str]]]:
    """
    将翻译后的代码签名转换为目标签名
    
    Args:
        translated_code: 翻译后的 Python 代码
        target_code: Python 原生代码 (ground truth)
        threshold: 匹配阈值
        
    Returns:
        (转换后的代码, 签名映射)
    """
    # 创建签名映射
    mapping = create_signature_mapping(translated_code, target_code, threshold)
    
    # 转换代码
    converted_code = transform_code(translated_code, mapping)
    
    return converted_code, mapping


def convert_file(
    translated_file: str,
    target_file: str,
    output_file: Optional[str] = None,
    threshold: float = 0.5
) -> Tuple[str, Dict[str, Dict[str, str]]]:
    """
    将翻译后的文件签名转换为目标签名
    
    Args:
        translated_file: 翻译后的 Python 文件路径
        target_file: Python 原生文件路径 (ground truth)
        output_file: 输出文件路径 (可选)
        threshold: 匹配阈值
        
    Returns:
        (转换后的代码, 签名映射)
    """
    with open(translated_file, 'r', encoding='utf-8') as f:
        translated_code = f.read()
    
    with open(target_file, 'r', encoding='utf-8') as f:
        target_code = f.read()
    
    converted_code, mapping = convert_code(translated_code, target_code, threshold)
    
    if output_file:
        os.makedirs(os.path.dirname(output_file) or '.', exist_ok=True)
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(converted_code)
    
    return converted_code, mapping


def batch_convert(
    translated_dir: str,
    target_dir: str,
    output_dir: str,
    threshold: float = 0.5
) -> Dict[str, Dict[str, Dict[str, str]]]:
    """
    批量转换目录中的所有文件
    
    Args:
        translated_dir: 翻译后代码目录
        target_dir: Python 原生代码目录 (ground truth)
        output_dir: 输出目录
        threshold: 匹配阈值
        
    Returns:
        所有文件的签名映射 {filename: {class_name: {source_method: target_method}}}
    """
    translated_path = Path(translated_dir)
    target_path = Path(target_dir)
    output_path = Path(output_dir)
    
    all_mappings = {}
    
    for translated_file in translated_path.glob("*.py"):
        filename = translated_file.name
        target_file = target_path / filename
        
        if not target_file.exists():
            print(f"跳过 {filename}: 目标文件不存在")
            continue
        
        output_file = output_path / filename
        
        try:
            _, mapping = convert_file(
                str(translated_file),
                str(target_file),
                str(output_file),
                threshold
            )
            all_mappings[filename] = mapping
            
            # 统计有效转换
            changes = sum(
                1 for class_map in mapping.values() 
                for src, tgt in class_map.items() if src != tgt
            )
            if changes > 0:
                print(f"✓ {filename}: {changes} 个方法签名已转换")
            else:
                print(f"○ {filename}: 无需转换")
                
        except Exception as e:
            print(f"✗ {filename}: 转换失败 - {e}")
    
    return all_mappings


def main():
    """命令行入口"""
    parser = argparse.ArgumentParser(
        description="将翻译后的 Python 代码函数签名转换为目标签名"
    )
    
    subparsers = parser.add_subparsers(dest='command', help='子命令')
    
    # 单文件转换
    single_parser = subparsers.add_parser('convert', help='转换单个文件')
    single_parser.add_argument('translated', help='翻译后的 Python 文件')
    single_parser.add_argument('target', help='Python 原生文件 (ground truth)')
    single_parser.add_argument('-o', '--output', help='输出文件路径')
    single_parser.add_argument('-t', '--threshold', type=float, default=0.5,
                               help='匹配阈值 (0.0-1.0)')
    
    # 批量转换
    batch_parser = subparsers.add_parser('batch', help='批量转换目录')
    batch_parser.add_argument('translated_dir', help='翻译后代码目录')
    batch_parser.add_argument('target_dir', help='Python 原生代码目录')
    batch_parser.add_argument('output_dir', help='输出目录')
    batch_parser.add_argument('-t', '--threshold', type=float, default=0.5,
                              help='匹配阈值 (0.0-1.0)')
    
    # 分析签名差异
    analyze_parser = subparsers.add_parser('analyze', help='分析签名差异')
    analyze_parser.add_argument('translated', help='翻译后的 Python 文件')
    analyze_parser.add_argument('target', help='Python 原生文件 (ground truth)')
    
    args = parser.parse_args()
    
    if args.command == 'convert':
        converted, mapping = convert_file(
            args.translated,
            args.target,
            args.output,
            args.threshold
        )
        
        if not args.output:
            print(converted)
        
        print("\n签名映射:")
        for class_name, method_map in mapping.items():
            print(f"类 {class_name}:")
            for src, tgt in method_map.items():
                if src != tgt:
                    print(f"  {src} -> {tgt}")
    
    elif args.command == 'batch':
        all_mappings = batch_convert(
            args.translated_dir,
            args.target_dir,
            args.output_dir,
            args.threshold
        )
        
        total_changes = sum(
            1 for file_map in all_mappings.values()
            for class_map in file_map.values()
            for src, tgt in class_map.items() if src != tgt
        )
        print(f"\n总计: {len(all_mappings)} 个文件处理完成, {total_changes} 个方法签名已转换")
    
    elif args.command == 'analyze':
        with open(args.translated, 'r', encoding='utf-8') as f:
            translated_code = f.read()
        with open(args.target, 'r', encoding='utf-8') as f:
            target_code = f.read()
        
        translated_sigs = extract_signatures(translated_code)
        target_sigs = extract_signatures(target_code)
        mapping = create_signature_mapping(translated_code, target_code)
        
        print("翻译后代码签名:")
        for class_name, class_sig in translated_sigs.items():
            print(f"  类 {class_name}:")
            for method_name in class_sig.methods:
                print(f"    - {method_name}")
        
        print("\n目标代码签名:")
        for class_name, class_sig in target_sigs.items():
            print(f"  类 {class_name}:")
            for method_name in class_sig.methods:
                print(f"    - {method_name}")
        
        print("\n需要转换的签名:")
        for class_name, method_map in mapping.items():
            for src, tgt in method_map.items():
                if src != tgt:
                    print(f"  {src} -> {tgt}")
    
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
