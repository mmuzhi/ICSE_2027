import json
import os
import glob

def simple_merge_jsonl(input_dir, output_file):
    """
    简化版的JSONL文件合并
    """
    jsonl_files = glob.glob(os.path.join(input_dir, "*.jsonl"))
    
    if not jsonl_files:
        print("没有找到JSONL文件")
        return
    
    all_data = []
    
    for file_path in jsonl_files:
        with open(file_path, 'r', encoding='utf-8') as f:
            for line in f:
                line = line.strip()
                if line:
                    try:
                        data = json.loads(line)
                        all_data.append(data)
                    except json.JSONDecodeError:
                        continue
    
    with open(output_file, 'w', encoding='utf-8') as f:
        for data in all_data:
            f.write(json.dumps(data, ensure_ascii=False) + '\n')
    
    print(f"合并完成! 共 {len(all_data)} 行数据")

# 使用方法
if __name__ == "__main__":
    input_directory = "/Users/bytedance/XLLM_COT/data/LCB"  # 替换为你的输入目录
    output_filename = "merged_output.jsonl"  # 输出文件名
    
    simple_merge_jsonl(input_directory, output_filename)