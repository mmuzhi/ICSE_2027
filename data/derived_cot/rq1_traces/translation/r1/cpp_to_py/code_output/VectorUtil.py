import math
from typing import List, Dict

class VectorUtil:
    @staticmethod
    def norm(vec: List[float]) -> float:
        s = 0.0
        for x in vec:
            s += x * x
        return math.sqrt(s)

    @staticmethod
    def normalize(vec: List[float]) -> List[float]:
        n = VectorUtil.norm(vec)
        if n == 0.0:
            return [0.0] * len(vec)
        return [x / n for x in vec]

    @staticmethod
    def similarity(vector_1: List[float], vector_2: List[float]) -> float:
        n1 = VectorUtil.norm(vector_1)
        n2 = VectorUtil.norm(vector_2)
        if n1 == 0.0 or n2 == 0.0:
            return 0.0
        dot = 0.0
        for i in range(len(vector_1)):
            dot += vector_1[i] * vector_2[i]
        return dot / (n1 * n2)

    @staticmethod
    def cosine_similarities(vector_1: List[float], vectors_all: List[List[float]]) -> List[float]:
        norm_vec1 = VectorUtil.norm(vector_1)
        similarities = []
        for vec in vectors_all:
            norm_vec = VectorUtil.norm(vec)
            if norm_vec == 0.0:
                similarities.append(0.0)
                continue
            if norm_vec1 == 0.0:
                dot_product = 0.0
            else:
                dot_product = 0.0
                for i in range(len(vector_1)):
                    dot_product += vector_1[i] * vec[i]
            denominator = norm_vec1 * norm_vec
            similarity_val = dot_product / denominator
            similarities.append(similarity_val)
        return similarities

    @staticmethod
    def n_similarity(vector_list_1: List[List[float]], vector_list_2: List[List[float]]) -> float:
        if not vector_list_1 or not vector_list_2:
            raise ValueError("At least one of the lists is empty.")
        n = len(vector_list_1[0])
        mean_vec1 = [0.0] * n
        mean_vec2 = [0.0] * n

        for vec in vector_list_1:
            for i in range(n):
                mean_vec1[i] += vec[i]

        for vec in vector_list_2:
            for i in range(n):
                mean_vec2[i] += vec[i]

        size1 = len(vector_list_1)
        size2 = len(vector_list_2)
        mean_vec1 = [x / size1 for x in mean_vec1]
        mean_vec2 = [x / size2 for x in mean_vec2]

        return VectorUtil.similarity(mean_vec1, mean_vec2)

    @staticmethod
    def compute_idf_weight_dict(total_num: int, number_dict: Dict[str, float]) -> Dict[str, float]:
        result = {}
        for key, count in number_dict.items():
            result[key] = math.log((total_num + 1.0) / (count + 1.0))
        return result