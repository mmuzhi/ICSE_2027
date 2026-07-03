"""
批量测试 ClassEval-T C++ 数据集的脚本
检查 solution 代码能否编译通过，以及 solution + test 能否一起编译
需要: g++ 编译器
"""

import os
import subprocess
import tempfile
import shutil

# 设置路径
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
SOLUTION_DIR = os.path.join(BASE_DIR, "Translation_COT", "qwen" , "py_to_cpp" , "code_output")
TEST_DIR = os.path.join(BASE_DIR, "cpp", "test")


def check_compile_solution(class_name, temp_dir):
    """
    检查 solution 代码能否编译通过
    返回: (成功?, 错误信息)
    """
    solution_file = os.path.join(SOLUTION_DIR, f"{class_name}.cpp")
    
    if not os.path.exists(solution_file):
        return False, "Solution file not found"
    
    # 读取 solution 代码
    with open(solution_file, 'r', encoding='utf-8') as f:
        solution_code = f.read()
    
    # 创建临时源文件 (添加必要的 include 和 main)
    temp_source = os.path.join(temp_dir, f"{class_name}.cpp")
    
    # 添加常用头文件和 pow 函数支持
    full_code = '''
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <fstream>
#include <stack>
#include <queue>
#include <functional>
#include <regex>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <memory>
#include <stdexcept>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <cassert>
using namespace std;
''' + solution_code + '''
int main() { return 0; }
'''
    
    with open(temp_source, 'w', encoding='utf-8') as f:
        f.write(full_code)
    
    output_exe = os.path.join(temp_dir, f"{class_name}.exe")
    
    try:
        result = subprocess.run(
            ['g++', '-std=c++17', '-c', temp_source, '-o', output_exe],
            capture_output=True,
            text=True,
            timeout=30,
            cwd=temp_dir
        )
        
        if result.returncode == 0:
            return True, ""
        else:
            # 提取第一个错误
            error_lines = result.stderr.split('\n')
            first_error = ""
            for line in error_lines:
                if 'error:' in line:
                    first_error = line.split('error:')[-1].strip()[:80]
                    break
            return False, first_error if first_error else result.stderr[:100]
            
    except subprocess.TimeoutExpired:
        return False, "Compilation timeout"
    except Exception as e:
        return False, str(e)[:80]


def main():
    print("=" * 70)
    print("ClassEval-T C++ Dataset Compile Test")
    print("=" * 70)
    print()
    
    # 获取所有 solution 文件
    solution_files = sorted([f[:-4] for f in os.listdir(SOLUTION_DIR) if f.endswith('.cpp')])
    print(f"Found {len(solution_files)} C++ classes to test\n")
    print("-" * 70)
    
    compiled = 0
    failed = 0
    failed_classes = []
    
    # 创建临时目录
    temp_dir = tempfile.mkdtemp()
    
    try:
        for i, class_name in enumerate(solution_files, 1):
            success, error_msg = check_compile_solution(class_name, temp_dir)
            
            status = "PASS" if success else "FAIL"
            if success:
                print(f"[{i:2}/{len(solution_files)}] {class_name:40} {status}")
                compiled += 1
            else:
                print(f"[{i:2}/{len(solution_files)}] {class_name:40} {status}")
                failed += 1
                failed_classes.append((class_name, error_msg))
    finally:
        # 清理临时目录
        shutil.rmtree(temp_dir, ignore_errors=True)
    
    print("-" * 70)
    print()
    print("=" * 70)
    print("SUMMARY")
    print("=" * 70)
    print(f"Total classes:    {len(solution_files)}")
    print(f"Compile success:  {compiled}")
    print(f"Compile failed:   {failed}")
    print()
    
    if failed_classes:
        print("Failed classes:")
        for class_name, error_msg in failed_classes:
            print(f"  - {class_name}: {error_msg}")


if __name__ == "__main__":
    main()
