"""
批量测试 ClassEval-T Python 数据集的脚本
计算 Pass@1 (类级别通过率) 和 CAM (测试用例级别通过率)
"""

import os
import sys
import unittest
import io
import tempfile
import shutil

# 设置路径
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
SOLUTION_DIR = os.path.join(BASE_DIR, "Translation_COT", "qwen" , "cpp_to_py" , "code_output")
TEST_DIR = os.path.join(BASE_DIR, "py", "test")


def run_single_class_test(class_name, solution_dir, test_dir):
    """
    运行单个类的测试
    返回: (总测试数, 通过数, 失败数, 错误信息)
    """
    solution_file = os.path.join(solution_dir, f"{class_name}.py")
    test_file = os.path.join(test_dir, f"{class_name}.py")
    
    if not os.path.exists(solution_file):
        return 0, 0, 0, "Solution file not found"
    if not os.path.exists(test_file):
        return 0, 0, 0, "Test file not found"
    
    temp_dir = tempfile.mkdtemp()
    original_dir = os.getcwd()
    
    try:
        os.chdir(temp_dir)
        
        with open(solution_file, 'r', encoding='utf-8') as f:
            solution_code = f.read()
        with open(test_file, 'r', encoding='utf-8') as f:
            test_code = f.read()
        
        namespace = {
            '__name__': '__main__',
            'unittest': unittest,
        }
        
        exec(solution_code, namespace)
        exec(test_code, namespace)
        
        loader = unittest.TestLoader()
        suite = unittest.TestSuite()
        
        for name, obj in namespace.items():
            if isinstance(obj, type) and issubclass(obj, unittest.TestCase) and obj is not unittest.TestCase:
                tests = loader.loadTestsFromTestCase(obj)
                suite.addTests(tests)
        
        stream = io.StringIO()
        runner = unittest.TextTestRunner(stream=stream, verbosity=0)
        result = runner.run(suite)
        
        total = result.testsRun
        failed = len(result.failures) + len(result.errors)
        passed = total - failed
        
        error_msg = ""
        if result.failures:
            for test, trace in result.failures[:1]:
                error_msg = trace.split('\n')[-2] if trace else ""
        if result.errors:
            for test, trace in result.errors[:1]:
                error_msg = trace.split('\n')[-2] if trace else ""
        
        return total, passed, failed, error_msg
        
    except Exception as e:
        return 0, 0, 0, f"{type(e).__name__}: {str(e)[:80]}"
    finally:
        os.chdir(original_dir)
        shutil.rmtree(temp_dir, ignore_errors=True)


def run_tests(solution_dir, test_dir, label=""):
    """
    运行所有测试并计算 Pass@1 和 CAM
    """
    solution_files = sorted([f[:-3] for f in os.listdir(solution_dir) if f.endswith('.py')])
    
    print(f"Found {len(solution_files)} classes to test")
    print("-" * 70)
    
    class_passed = 0  # 完全通过的类数量
    class_total = 0   # 有效测试的类数量
    
    test_passed_total = 0  # 通过的测试用例总数
    test_total = 0         # 测试用例总数
    
    failed_classes = []
    
    for i, class_name in enumerate(solution_files, 1):
        total, passed, failed, error_msg = run_single_class_test(class_name, solution_dir, test_dir)
        
        if total > 0:
            class_total += 1
            test_total += total
            test_passed_total += passed
            
            if failed == 0:
                class_passed += 1
                status = "PASS"
            else:
                status = "FAIL"
                failed_classes.append((class_name, error_msg))
        else:
            status = "SKIP"
            if error_msg:
                failed_classes.append((class_name, error_msg))
        
        print(f"[{i:2}/{len(solution_files)}] {class_name:40} {status} ({passed}/{total} tests)")
    
    print("-" * 70)
    print()
    
    # 计算 Pass@1 和 CAM
    pass_at_1 = (class_passed / class_total * 100) if class_total > 0 else 0
    cam = (test_passed_total / test_total * 100) if test_total > 0 else 0
    
    return {
        'label': label,
        'class_total': class_total,
        'class_passed': class_passed,
        'test_total': test_total,
        'test_passed': test_passed_total,
        'pass_at_1': pass_at_1,
        'cam': cam,
        'failed_classes': failed_classes
    }


def print_results(results):
    """打印测试结果"""
    print("=" * 70)
    print("RESULTS" + (f" - {results['label']}" if results['label'] else ""))
    print("=" * 70)
    print()
    print(f"  Classes tested:     {results['class_total']}")
    print(f"  Classes passed:     {results['class_passed']}")
    print(f"  Total test cases:   {results['test_total']}")
    print(f"  Test cases passed:  {results['test_passed']}")
    print()
    print(f"  Pass@1 (Class-level):    {results['pass_at_1']:.2f}%")
    print(f"  CAM (Test case-level):   {results['cam']:.2f}%")
    print()
    
    if results['failed_classes']:
        print("Failed classes:")
        for class_name, error_msg in results['failed_classes'][:20]:
            print(f"  - {class_name}: {error_msg[:60]}")
        if len(results['failed_classes']) > 20:
            print(f"  ... and {len(results['failed_classes']) - 20} more")


def main():
    import argparse
    parser = argparse.ArgumentParser(description='Test ClassEval-T Python classes')
    parser.add_argument('--solution-dir', '-s', default=SOLUTION_DIR,
                        help='Path to solution directory')
    parser.add_argument('--test-dir', '-t', default=TEST_DIR,
                        help='Path to test directory')
    parser.add_argument('--label', '-l', default='',
                        help='Label for this test run')
    args = parser.parse_args()
    
    print("=" * 70)
    print("ClassEval-T Python Test Runner")
    print("=" * 70)
    print()
    print(f"Solution dir: {args.solution_dir}")
    print(f"Test dir:     {args.test_dir}")
    print()
    
    results = run_tests(args.solution_dir, args.test_dir, args.label)
    print_results(results)


if __name__ == "__main__":
    main()
