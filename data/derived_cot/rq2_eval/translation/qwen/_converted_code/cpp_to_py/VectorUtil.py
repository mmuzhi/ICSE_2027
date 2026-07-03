import math
import numpy as np
from typing import List, Dict, Tuple

class VectorUtil:
    @staticmethod
    def norm(vec: List[float]) -> float:
        return math.sqrt(sum(x**2 for x in vec))
    
    @staticmethod
    def normalize(vec: List[float]) -> List[float]:
        norm_val = VectorUtil.norm(vec)
        if norm_val == 0.0:
            return [0.0] * len(vec)
        return [x / norm_val for x in vec]
    
    @staticmethod
    def similarity(vec1: List[float], vec2: List[float]) -> float:
        norm_vec1 = VectorUtil.normalize(vec1)
        norm_vec2 = VectorUtil.normalize(vec2)
        dot_product = sum(x * y for x, y in zip(norm_vec1, norm_vec2))
        return dot_product
    
    @staticmethod
    def cosine_similarities(vec: List[float], vec_list: List[List[float]]) -> List[float]:
        if not vec_list:
            return []
        norm_vec = VectorUtil.norm(vec)
        similarities = []
        for v in vec_list:
            norm_v = VectorUtil.norm(v)
            if norm_v == 0.0:
                similarities.append(0.0)
                continue
            dot_product = sum(x * y for x, y in zip(vec, v))
            similarity_val = dot_product / (norm_vec * norm_v)
            similarities.append(similarity_val)
        return similarities
    
    @staticmethod
    def n_similarity(vec_list1: List[List[float]], vec_list2: List[List[float]]) -> float:
        if not vec_list1 or not vec_list2:
            raise ValueError("At least one of the lists is empty.")
        mean_vec1 = [0.0] * len(vec_list1[0])
        mean_vec2 = [0.0] * len(vec_list2[0])
        
        for vec in vec_list1:
            for i, val in enumerate(vec):
                mean_vec1[i] += val
        for vec in vec_list2:
            for i, val in enumerate(vec):
                mean_vec2[i] += val
        
        for i in range(len(mean_vec1)):
            mean_vec1[i] /= len(vec_list1)
            mean_vec2[i] /= len(vec_list2)
        
        return VectorUtil.similarity(mean_vec1, mean_vec2)
    
    @staticmethod
    def compute_idf_weight_dict(total_num: int, number_dict: Dict[str, float]) -> Dict[str, float]:
        result = {}
        index_to_key = {}
        count_list = []
        index = 0
        
        for key, count_val in number_dict.items():
            index_to_key[index] = key
            count_list.append(count_val)
            index += 1
        
        a = [math.log((total_num + 1.0) / (count + 1.0)) for count in count_list]
        
        for i, key in index_to_key.items():
            result[key] = a[i]
        
        return result