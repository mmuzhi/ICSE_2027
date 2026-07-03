import json
import tiktoken

def filter_cot_by_token_length(input_file, output_file, deleted_log_file, max_tokens=30000):
    """
    过滤COT字段token超过指定长度的数据
    
    参数:
        input_file: 输入JSON文件路径
        output_file: 输出过滤后的JSON文件路径
        deleted_log_file: 删除记录文件路径
        max_tokens: 最大token数量，默认30000
    """
    # 初始化tokenizer
    encoding = tiktoken.get_encoding("cl100k_base")
    
    total_count = 0
    kept_count = 0
    deleted_count = 0
    deleted_tasks = []
    
    # 读取并处理文件
    with open(input_file, 'r', encoding='utf-8') as f_in, \
         open(output_file, 'w', encoding='utf-8') as f_out:
        
        for line in f_in:
            total_count += 1
            try:
                data = json.loads(line.strip())
                
                # 检查是否有COT字段
                if 'cot' in data:
                    # 计算token数量
                    tokens = encoding.encode(data['cot'])
                    token_count = len(tokens)
                    
                    # 判断是否超过限制
                    if token_count > max_tokens:
                        deleted_count += 1
                        # 记录被删除的task_id和token数量
                        task_id = data.get('task_id', f'unknown_{total_count}')
                        deleted_tasks.append({
                            'task_id': task_id,
                            'token_count': token_count
                        })
                    else:
                        # 保留数据
                        kept_count += 1
                        f_out.write(json.dumps(data, ensure_ascii=False) + '\n')
                else:
                    # 没有COT字段的数据也保留
                    kept_count += 1
                    f_out.write(json.dumps(data, ensure_ascii=False) + '\n')
                    
            except json.JSONDecodeError:
                print(f"警告: 第 {total_count} 行JSON解析失败，跳过")
                continue
    
    # 写入删除记录
    with open(deleted_log_file, 'w', encoding='utf-8') as f_log:
        f_log.write(f"删除记录 - Token超过{max_tokens}的数据\n")
        f_log.write("=" * 60 + "\n")
        f_log.write(f"总处理数量: {total_count}\n")
        f_log.write(f"保留数量: {kept_count}\n")
        f_log.write(f"删除数量: {deleted_count}\n")
        f_log.write("=" * 60 + "\n\n")
        
        if deleted_tasks:
            f_log.write("删除的任务列表:\n")
            f_log.write("-" * 60 + "\n")
            for item in deleted_tasks:
                f_log.write(f"Task ID: {item['task_id']}, Token数量: {item['token_count']}\n")
    
    # 打印统计信息
    print("=" * 60)
    print("数据过滤完成")
    print("=" * 60)
    print(f"总处理数量: {total_count}")
    print(f"保留数量: {kept_count}")
    print(f"删除数量: {deleted_count}")
    print(f"删除比例: {deleted_count/total_count*100:.2f}%")
    print()
    print(f"过滤后的数据已保存到: {output_file}")
    print(f"删除记录已保存到: {deleted_log_file}")
    print("=" * 60)


if __name__ == "__main__":
    # 配置文件路径
    input_file = "/mnt/sda/yz/projects/XLLM_COT/data/LCB/Generate_COT/v4_v6/results.jsonl"
    output_file = "/mnt/sda/yz/projects/XLLM_COT/data/LCB/Generate_COT/v4_v6/results_filtered.jsonl"
    deleted_log_file = "/mnt/sda/yz/projects/XLLM_COT/data/LCB/Generate_COT/v4_v6/deleted_log.txt"
    
    try:
        filter_cot_by_token_length(
            input_file=input_file,
            output_file=output_file,
            deleted_log_file=deleted_log_file,
            max_tokens=30000
        )
    except FileNotFoundError:
        print(f"错误: 找不到文件 '{input_file}'")
        print("请将文件路径修改为实际的文件路径")
    except Exception as e:
        print(f"发生错误: {e}")