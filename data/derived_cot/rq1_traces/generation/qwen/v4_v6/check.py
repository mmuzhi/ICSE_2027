"""
清理 JSONL 文件中的无效条目，并删除对应的 txt 文件
"""

import json
import os
from pathlib import Path


def clean_jsonl_and_files(
    jsonl_path: str,
    output_dir: str,
    output_jsonl: str = None,
    dry_run: bool = True
):
    """
    清理 JSONL 文件中的无效条目，并删除对应的 txt 文件
    
    Args:
        jsonl_path: 输入的 JSONL 文件路径
        output_dir: txt 文件所在目录（如 v4_output/）
        output_jsonl: 输出的清理后 JSONL 文件路径（默认：原文件名_cleaned.jsonl）
        dry_run: 是否只预览不实际删除（默认 True）
    """
    
    if output_jsonl is None:
        output_jsonl = jsonl_path.replace('.jsonl', '_cleaned.jsonl')
    
    print("="*70)
    print("🧹 JSONL 清理工具")
    print("="*70)
    print(f"输入文件: {jsonl_path}")
    print(f"输出文件: {output_jsonl}")
    print(f"TXT 目录: {output_dir}")
    print(f"模式: {'🔍 预览模式（不会实际删除）' if dry_run else '⚠️  执行模式（会实际删除文件）'}")
    print("="*70)
    print()
    
    # 统计信息
    total_lines = 0
    valid_entries = []
    invalid_entries = []
    txt_files_to_delete = []
    
    # 读取并分析 JSONL 文件
    with open(jsonl_path, 'r', encoding='utf-8') as f:
        for line_num, line in enumerate(f, 1):
            total_lines += 1
            
            # 跳过空行
            if not line.strip():
                print(f"⚠️  Line {line_num}: 空行，跳过")
                invalid_entries.append({
                    'line_num': line_num,
                    'reason': '空行',
                    'task_id': None
                })
                continue
            
            # 解析 JSON
            try:
                sol = json.loads(line)
            except json.JSONDecodeError as e:
                print(f"❌ Line {line_num}: JSON 解析错误 - {e}")
                invalid_entries.append({
                    'line_num': line_num,
                    'reason': f'JSON 解析错误: {e}',
                    'task_id': None
                })
                continue
            
            # 提取 task_id
            task_id = sol.get('task_id') or sol.get('question_id') or sol.get('id')
            
            if not task_id:
                print(f"❌ Line {line_num}: 缺少 task_id（字段: {list(sol.keys())}）")
                invalid_entries.append({
                    'line_num': line_num,
                    'reason': '缺少 task_id',
                    'task_id': None
                })
                continue
            
            # 提取代码
            code = sol.get('answer') or sol.get('solution') or sol.get('code') or ''
            
            if len(code) < 20:
                print(f"❌ Line {line_num}: 代码太短（{len(code)} 字符）- task_id: {task_id}")
                invalid_entries.append({
                    'line_num': line_num,
                    'reason': f'代码太短（{len(code)} 字符）',
                    'task_id': task_id
                })
                
                # 检查对应的 txt 文件是否存在
                txt_file = Path(output_dir) / f"{task_id}.txt"
                if txt_file.exists():
                    txt_files_to_delete.append(str(txt_file))
                
                continue
            
            # 有效条目
            valid_entries.append(line)
    
    # 打印统计信息
    print()
    print("="*70)
    print("📊 统计信息")
    print("="*70)
    print(f"总行数: {total_lines}")
    print(f"✅ 有效条目: {len(valid_entries)}")
    print(f"❌ 无效条目: {len(invalid_entries)}")
    print(f"🗑️  需要删除的 txt 文件: {len(txt_files_to_delete)}")
    print()
    
    # 显示无效条目详情
    if invalid_entries:
        print("📋 无效条目详情:")
        for entry in invalid_entries:
            task_id_info = f"task_id: {entry['task_id']}" if entry['task_id'] else "无 task_id"
            print(f"   Line {entry['line_num']}: {entry['reason']} ({task_id_info})")
        print()
    
    # 显示要删除的文件
    if txt_files_to_delete:
        print("📁 将删除的 txt 文件:")
        for txt_file in txt_files_to_delete:
            print(f"   {txt_file}")
        print()
    
    # 执行操作
    if dry_run:
        print("="*70)
        print("🔍 预览模式：未进行任何修改")
        print("   如需实际执行，请设置 dry_run=False")
        print("="*70)
    else:
        print("="*70)
        print("⚠️  开始执行清理操作...")
        print("="*70)
        
        # 写入清理后的 JSONL 文件
        with open(output_jsonl, 'w', encoding='utf-8') as f:
            for line in valid_entries:
                f.write(line)
        print(f"✅ 已保存清理后的 JSONL 文件: {output_jsonl}")
        
        # 删除对应的 txt 文件
        deleted_count = 0
        for txt_file in txt_files_to_delete:
            try:
                os.remove(txt_file)
                deleted_count += 1
                print(f"   🗑️  已删除: {txt_file}")
            except Exception as e:
                print(f"   ❌ 删除失败: {txt_file} - {e}")
        
        print(f"\n✅ 成功删除 {deleted_count}/{len(txt_files_to_delete)} 个 txt 文件")
        print("="*70)
    
    return {
        'total_lines': total_lines,
        'valid_entries': len(valid_entries),
        'invalid_entries': len(invalid_entries),
        'txt_files_to_delete': len(txt_files_to_delete)
    }


def main():
    import argparse
    
    parser = argparse.ArgumentParser(
        description='清理 JSONL 文件中的无效条目，并删除对应的 txt 文件',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
使用示例:
  # 1. 预览模式（不会实际删除）
  python clean_invalid_entries.py results.jsonl v4_output/
  
  # 2. 执行模式（实际删除）
  python clean_invalid_entries.py results.jsonl v4_output/ --execute
  
  # 3. 指定输出文件名
  python clean_invalid_entries.py results.jsonl v4_output/ -o results_clean.jsonl --execute
        """
    )
    
    parser.add_argument('jsonl_file', help='输入的 JSONL 文件路径')
    parser.add_argument('output_dir', help='txt 文件所在目录')
    parser.add_argument('-o', '--output', help='输出的清理后 JSONL 文件路径（默认：原文件名_cleaned.jsonl）')
    parser.add_argument('--execute', action='store_true', help='实际执行删除操作（默认只预览）')
    
    args = parser.parse_args()
    
    # 检查文件是否存在
    if not Path(args.jsonl_file).exists():
        print(f"❌ 错误: 文件不存在: {args.jsonl_file}")
        return
    
    if not Path(args.output_dir).exists():
        print(f"❌ 错误: 目录不存在: {args.output_dir}")
        return
    
    # 执行清理
    clean_jsonl_and_files(
        jsonl_path=args.jsonl_file,
        output_dir=args.output_dir,
        output_jsonl=args.output,
        dry_run=not args.execute
    )


if __name__ == "__main__":
    main()