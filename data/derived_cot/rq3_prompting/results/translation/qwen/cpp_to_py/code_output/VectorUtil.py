import math
from typing import List, Dict

def norm(vec: List[float]) -> float:
    if not vec:
        return 0.0
    return math.sqrt(sum(x * x for x in vec))

def normalize(vec: List[float]) -> List[float]:
    norm_val = norm(vec)
    if norm_val == 0.0:
        return []
    return [x / norm_val for x in vec]

def similarity(vec1: List[float], vec2: List[float]) -> float:
    n1 = normalize(vec1)
    n2 = normalize(vec2)
    if len(n1) != len(n2):
        raise ValueError("Vectors must have the same length")
    return sum(x * y for x, y in zip(n1, n2))

def cosine_similarities(vec: List[float], vec_list: List[List[float]]) -> List[float]:
    if not vec_list:
        return []
    n = len(vec)
    for v in vec_list:
        if len(v) != n:
            raise ValueError("All vectors must have the same length as the given vector")
    norm_vec1 = norm(vec)
    result = []
    for v in vec_list:
        norm_vec_all = norm(v)
        if norm_vec_all == 0.0:
            result.append(0.0)
            continue
        dot_product = sum(x * y for x, y in zip(vec, v))
        similarity = dot_product / (norm_vec1 * norm_vec_all)
        result.append(similarity)
    return result

def n_similarity(vec_list1: List[List[float]], vec_list2: List[List[float]]) -> float:
    if not vec_list1 or not vec_list2:
        raise ValueError("At least one of the lists is empty")
    n = len(vec_list1[0]) if vec_list1 else 0
    for vec in vec_list1:
        if len(vec) != n:
            raise ValueError("All vectors in vec_list1 must have the same length")
    n2 = len(vec_list2[0]) if vec_list2 else 0
    for vec in vec_list2:
        if len(vec) != n2:
            raise ValueError("All vectors in vec_list2 must have the same length")
    if n != n2:
        raise ValueError("Vectors in vec_list1 and vec_list2 must have the same length")
    mean1 = [0.0] * n
    mean2 = [0.0] * n
    for vec in vec_list1:
        for i, x in enumerate(vec):
            mean1[i] += x
    for vec in vec_list2:
        for i, x in enumerate(vec):
            mean2[i] += x
    mean1 = [x / len(vec_list1) for x in mean1]
    mean2 = [x / len(vec_list2) for x in mean2]
    return similarity(mean1, mean2)

def compute_idf_weight_dict(total_num: int, number_dict: Dict[str, float]) -> Dict[str, float]:
    if not number_dict:
        return {}
    keys = list(number_dict.keys())
    counts = [number_dict[key] for key in keys]
    idf_weights = [math.log((total_num + 1) / (count + 1)) for count in counts]
    return dict(zip(keys, idf_weights))