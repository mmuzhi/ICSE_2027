import json
import argparse
import ast
import re
from pathlib import Path
from typing import Tuple, List


def is_valid_python_code(code: str) -> Tuple[bool, str]:
    """
    检查是否是有效的完整Python代码
    
    Returns:
        (is_valid, reason): 是否有效和原因
    """
    if not code or not code.strip():
        return False, "代码为空"
    
    code = code.strip()
    
    # 1. 检查是否包含过多非代码内容（解释性文字）
    # 去掉注释和字符串后，检查是否有大段的普通文字
    lines = code.split('\n')
    non_empty_lines = [l for l in lines if l.strip() and not l.strip().startswith('#')]
    
    if len(non_empty_lines) == 0:
        return False, "只有注释或空行"
    
    # 检查是否有明显的自然语言标记（中英文）
    natural_lang_patterns = [
        r'(这是|这里|代码如下|解释|说明|注意|以下是)',  # 中文解释
        r'(Here is|Here\'s|The code|Explanation|Note that|As follows)',  # 英文解释
        r'^(思考|分析|解决方案|答案)[:：]',  # 标题式文字
    ]
    
    first_few_lines = '\n'.join(lines[:5])
    for pattern in natural_lang_patterns:
        if re.search(pattern, first_few_lines, re.IGNORECASE):
            return False, f"包含解释性文字: {pattern}"
    
    # 2. 检查代码是否被截断
    # 常见的截断标志
    truncation_indicators = [
        r'\.\.\.+\s*$',  # 以 ... 结尾
        r'\[继续\]',
        r'\[未完\]',
        r'\(continued\)',
        r'\(more\.\.\.\)',
    ]
    
    last_lines = '\n'.join(lines[-3:])
    for pattern in truncation_indicators:
        if re.search(pattern, last_lines, re.IGNORECASE):
            return False, f"代码被截断: {pattern}"
    
    # 3. 检查括号/引号是否匹配
    brackets = {'(': ')', '[': ']', '{': '}'}
    stack = []
    in_string = False
    string_char = None
    escape_next = False
    
    for char in code:
        if escape_next:
            escape_next = False
            continue
            
        if char == '\\':
            escape_next = True
            continue
        
        # 处理字符串
        if char in ['"', "'"]:
            if not in_string:
                in_string = True
                string_char = char
            elif char == string_char:
                in_string = False
                string_char = None
            continue
        
        if in_string:
            continue
        
        # 处理括号
        if char in brackets:
            stack.append(char)
        elif char in brackets.values():
            if not stack:
                return False, f"括号不匹配: 多余的 {char}"
            open_bracket = stack.pop()
            if brackets[open_bracket] != char:
                return False, f"括号不匹配: {open_bracket} 与 {char}"
    
    if stack:
        return False, f"括号未闭合: {stack}"
    
    if in_string:
        return False, "字符串未闭合"
    
    # 4. 尝试用 ast 解析（最严格的检查）
    try:
        ast.parse(code)
    except SyntaxError as e:
        return False, f"语法错误: {e.msg} (行 {e.lineno})"
    except Exception as e:
        return False, f"解析错误: {str(e)}"
    
    # 5. 检查是否是完整的Python代码结构
    # 至少应该有函数定义、类定义或可执行语句
    has_function = bool(re.search(r'\bdef\s+\w+\s*\(', code))
    has_class = bool(re.search(r'\bclass\s+\w+', code))
    has_import = bool(re.search(r'\bimport\s+\w+|\bfrom\s+\w+', code))
    has_assignment = bool(re.search(r'\w+\s*=', code))
    
    if not (has_function or has_class or (has_import and has_assignment)):
        # 检查是否只是一个表达式或不完整的代码片段
        if len(non_empty_lines) < 3:
            return False, "代码过短，可能不完整"
    
    # 6. 检查是否以不完整的语句结尾
    last_line = lines[-1].rstrip() if lines else ""
    incomplete_endings = [
        r'^\s*\w+\s*=\s*$',  # 赋值语句没有右值
        r':\s*$',  # 以冒号结尾但没有缩进内容
        r',\s*$',  # 以逗号结尾
        r'\\\s*$',  # 以续行符结尾
    ]
    
    for pattern in incomplete_endings:
        if re.search(pattern, last_line):
            return False, f"代码不完整: 以异常方式结尾"
    
    return True, "代码有效"


def clean_empty_answers(jsonl_path: str, output_dir: str = None, 
                       output_jsonl: str = None, dry_run: bool = False,
                       check_code_validity: bool = True):
    """
    删除 answer 为空或代码无效的记录，并删除对应的 txt 文件
    
    Args:
        jsonl_path: 输入的 JSONL 文件路径
        output_dir: 存放 txt 文件的目录（默认为 jsonl 文件同目录下的 output 文件夹）
        output_jsonl: 输出的 JSONL 文件路径（默认覆盖原文件）
        dry_run: 如果为 True，只显示会删除什么，不实际删除
        check_code_validity: 是否检查代码有效性
    """
    jsonl_path = Path(jsonl_path)
    
    # 确定 output 目录
    if output_dir is None:
        output_dir = jsonl_path.parent / "output"
    else:
        output_dir = Path(output_dir)
    
    # 确定输出文件
    if output_jsonl is None:
        output_jsonl = jsonl_path
    else:
        output_jsonl = Path(output_jsonl)
    
    print(f"📂 读取文件: {jsonl_path}")
    print(f"📁 Output 目录: {output_dir}")
    print(f"{'🔍 检查代码有效性: 启用' if check_code_validity else '⚠️  检查代码有效性: 禁用'}")
    print(f"{'🔍 [DRY RUN] ' if dry_run else ''}开始处理...\n")
    
    # 读取所有记录
    valid_records = []
    invalid_records = []
    
    # 统计不同类型的问题
    stats = {
        'empty': [],
        'invalid_code': [],
        'parse_error': []
    }
    
    with open(jsonl_path, 'r', encoding='utf-8') as f:
        for line_num, line in enumerate(f, 1):
            line = line.strip()
            if not line:
                continue
            
            try:
                record = json.loads(line)
                task_id = record.get('task_id', f'unknown_{line_num}')
                answer = record.get('answer', '')
                
                # 检查 answer 是否为空
                if not answer or answer.strip() == '':
                    invalid_records.append((task_id, record, 'empty'))
                    stats['empty'].append(task_id)
                    print(f"❌ 空答案: {task_id}")
                    continue
                
                # 检查代码有效性
                if check_code_validity:
                    is_valid, reason = is_valid_python_code(answer)
                    if not is_valid:
                        invalid_records.append((task_id, record, 'invalid_code'))
                        stats['invalid_code'].append((task_id, reason))
                        print(f"⚠️  无效代码: {task_id}")
                        print(f"   原因: {reason}")
                        continue
                
                valid_records.append(record)
                    
            except json.JSONDecodeError as e:
                print(f"⚠️  警告: 第 {line_num} 行 JSON 解析失败: {e}")
                stats['parse_error'].append(line_num)
                continue
    
    print(f"\n{'='*60}")
    print(f"📊 统计信息:")
    print(f"  总记录数: {len(valid_records) + len(invalid_records)}")
    print(f"  有效记录: {len(valid_records)}")
    print(f"  无效记录: {len(invalid_records)}")
    print(f"    - 空答案: {len(stats['empty'])}")
    print(f"    - 无效代码: {len(stats['invalid_code'])}")
    print(f"  JSON解析失败: {len(stats['parse_error'])}")
    print(f"{'='*60}\n")
    
    if not invalid_records:
        print("✅ 没有发现需要删除的记录！")
        return
    
    # 显示无效代码的详细原因（前10个）
    if stats['invalid_code']:
        print(f"🔍 无效代码详情 (显示前10个):")
        for task_id, reason in stats['invalid_code'][:10]:
            print(f"  {task_id}: {reason}")
        if len(stats['invalid_code']) > 10:
            print(f"  ... 还有 {len(stats['invalid_code']) - 10} 个")
        print()
    
    # 删除对应的 txt 文件
    deleted_files = []
    missing_files = []
    
    for task_id, _, reason_type in invalid_records:
        txt_file = output_dir / f"{task_id}.txt"
        
        if txt_file.exists():
            if not dry_run:
                txt_file.unlink()
                deleted_files.append((task_id, reason_type))
                print(f"🗑️  删除文件: {txt_file.name} ({reason_type})")
            else:
                deleted_files.append((task_id, reason_type))
                print(f"🔍 [DRY RUN] 将删除: {txt_file.name} ({reason_type})")
        else:
            missing_files.append(task_id)
            print(f"⚠️  文件不存在: {txt_file.name}")
    
    # 保存清理后的 JSONL
    if not dry_run:
        # 如果是覆盖原文件，先备份
        if output_jsonl == jsonl_path:
            backup_path = jsonl_path.with_suffix('.jsonl.backup')
            print(f"\n💾 备份原文件到: {backup_path}")
            jsonl_path.rename(backup_path)
        
        with open(output_jsonl, 'w', encoding='utf-8') as f:
            for record in valid_records:
                f.write(json.dumps(record, ensure_ascii=False) + '\n')
        
        print(f"✅ 已保存清理后的文件: {output_jsonl}")
        
        # 保存问题报告
        report_path = output_jsonl.parent / f"{output_jsonl.stem}_report.txt"
        with open(report_path, 'w', encoding='utf-8') as f:
            f.write("="*60 + "\n")
            f.write("无效记录详细报告\n")
            f.write("="*60 + "\n\n")
            
            f.write(f"空答案 ({len(stats['empty'])}):\n")
            for task_id in stats['empty']:
                f.write(f"  - {task_id}\n")
            f.write("\n")
            
            f.write(f"无效代码 ({len(stats['invalid_code'])}):\n")
            for task_id, reason in stats['invalid_code']:
                f.write(f"  - {task_id}: {reason}\n")
            f.write("\n")
            
            if stats['parse_error']:
                f.write(f"JSON解析失败 ({len(stats['parse_error'])}):\n")
                for line_num in stats['parse_error']:
                    f.write(f"  - 行 {line_num}\n")
        
        print(f"📝 问题报告已保存: {report_path}")
    else:
        print(f"\n🔍 [DRY RUN] 将保存到: {output_jsonl}")
    
    # 最终统计
    print(f"\n{'='*60}")
    print(f"🎯 完成统计:")
    print(f"  删除的记录: {len(invalid_records)}")
    print(f"    - 空答案: {len(stats['empty'])}")
    print(f"    - 无效代码: {len(stats['invalid_code'])}")
    print(f"  删除的文件: {len(deleted_files)}")
    print(f"  未找到的文件: {len(missing_files)}")
    print(f"  剩余有效记录: {len(valid_records)}")
    print(f"{'='*60}")
    
    if missing_files:
        print(f"\n⚠️  以下 task_id 没有对应的 txt 文件:")
        for task_id in missing_files[:10]:
            print(f"  - {task_id}")
        if len(missing_files) > 10:
            print(f"  ... 还有 {len(missing_files) - 10} 个")


def main():
    parser = argparse.ArgumentParser(
        description="清理 JSONL 文件中 answer 为空或代码无效的记录，并删除对应的 txt 文件",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例用法:
  # 基本用法（dry run 模式）
  python script.py results.jsonl --dry-run
  
  # 实际执行清理
  python script.py results.jsonl
  
  # 指定输出文件和目录
  python script.py results.jsonl --output_jsonl results_cleaned.jsonl --output_dir ./output
  
  # 只检查空答案，不检查代码有效性
  python script.py results.jsonl --no-check-code
        """
    )
    parser.add_argument(
        'jsonl_path',
        type=str,
        nargs='?',
        default="/mnt/sda/yz/projects/XLLM_COT/data/LCB/Generate_COT/r1/v4_v6/results.jsonl",
        help="输入的 JSONL 文件路径"
    )
    parser.add_argument(
        '--output_dir',
        type=str,
        default="/mnt/sda/yz/projects/XLLM_COT/data/LCB/Generate_COT/r1/v4_v6/v4_output",
        help="存放 txt 文件的目录（默认为 jsonl 文件同目录下的 output 文件夹）"
    )
    parser.add_argument(
        '--output_jsonl',
        type=str,
        default=None,
        help="输出的 JSONL 文件路径（默认覆盖原文件，会先备份）"
    )
    parser.add_argument(
        '--dry-run',
        action='store_true',
        help="只显示会删除什么，不实际删除"
    )
    parser.add_argument(
        '--no-check-code',
        action='store_true',
        help="不检查代码有效性，只删除空答案"
    )
    
    args = parser.parse_args()
    
    clean_empty_answers(
        jsonl_path=args.jsonl_path,
        output_dir=args.output_dir,
        output_jsonl=args.output_jsonl,
        dry_run=args.dry_run,
        check_code_validity=not args.no_check_code
    )


if __name__ == '__main__':
    main()