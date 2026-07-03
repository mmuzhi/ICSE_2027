import json

def simple_filter_jsonl(input_file, output_file):
    """
    简化版：过滤JSONL文件，只保留easy和middle难度
    """
    kept_count = 0
    total_count = 0
    
    with open(input_file, 'r', encoding='utf-8') as infile, \
         open(output_file, 'w', encoding='utf-8') as outfile:
        
        for line in infile:
            line = line.strip()
            if not line:
                continue
                
            total_count += 1
            
            try:
                data = json.loads(line)
                difficulty = data.get('difficulty', '').lower()
                
                if difficulty in ['easy', 'medium']:
                    outfile.write(json.dumps(data, ensure_ascii=False) + '\n')
                    kept_count += 1
                    
            except json.JSONDecodeError:
                continue
    
    print(f"过滤完成! 原始数据: {total_count} 行, 保留: {kept_count} 行")

# 使用方法
if __name__ == "__main__":
    simple_filter_jsonl("/mnt/sda/yz/projects/XLLM_COT/data/LCB/v4_v6.jsonl", "filtered_easy_middle.jsonl")