import math
from typing import List, Dict, Union

def similarity(vector1: List[float], vector2: List[float]) -> float:
    dot_product = sum(v1 * v2 for v1, v2 in zip(vector1, vector2))
    norm1 = math.sqrt(sum(v ** 2 for v in vector1))
    norm2 = math.sqrt(sum(v ** 2 for v in vector2))
    denominator = norm1 * norm2
    return 0.0 if denominator == 0 else dot_product / denominator

def cosine_similarities(vector1: List[float], vectors_all: List[List[float]]) -> List[float]:
    norm1 = math.sqrt(similarity(vector1, vector1))
    if norm1 == 0:
        return [0.0] * len(vectors_all)
    result = []
    for vector2 in vectors_all:
        norm2 = math.sqrt(similarity(vector2, vector2))
        if norm2 == 0:
            result.append(0.0)
        else:
            result.append(similarity(vector1, vector2) / (norm1 * norm2))
    return result

def n_similarity(vector_list1: List[List[float]], vector_list2: List[List[float]]) -> float:
    if not vector_list1 or not vector_list2:
        raise ValueError("At least one of the passed lists is empty.")
    avg_vector1 = average_vector(vector_list1)
    avg_vector2 = average_vector(vector_list2)
    return similarity(avg_vector1, avg_vector2)

def compute_idf_weight_dict(total_num: int, number_dict: Dict[str, float]) -> Dict[str, float]:
    return {term: math.log((total_num + 1) / (count + 1)) for term, count in number_dict.items()}

def dot_product(vector1: List[float], vector2: List[float]) -> float:
    return sum(v1 * v2 for v1, v2 in zip(vector1, vector2))

def average_vector(vectors: List[List[float]]) -> List[float]:
    if not vectors:
        return []
    avg_vector = [0.0] * len(vectors[0])
    for vector in vectors:
        for i, v in enumerate(vector):
            avg_vector[i] += v
    return [v / len(vectors) for v in avg_vector]