import math
from typing import List, Dict


class VectorUtil:

    @staticmethod
    def _norm(vec: List[float]) -> float:
        return math.sqrt(sum(val * val for val in vec))

    @staticmethod
    def _normalize(vec: List[float]) -> List[float]:
        vec_norm = VectorUtil._norm(vec)
        if vec_norm == 0.0:
            return [0.0] * len(vec)
        return [val / vec_norm for val in vec]

    @staticmethod
    def similarity(vector_1: List[float], vector_2: List[float]) -> float:
        norm_vec1 = VectorUtil._normalize(vector_1)
        norm_vec2 = VectorUtil._normalize(vector_2)
        dot_product = sum(a * b for a, b in zip(norm_vec1, norm_vec2))
        return dot_product

    @staticmethod
    def cosine_similarities(vector_1: List[float], vectors_all: List[List[float]]) -> List[float]:
        similarities: List[float] = []
        norm_vec1 = VectorUtil._norm(vector_1)
        for vec in vectors_all:
            norm_vec_all = VectorUtil._norm(vec)
            if norm_vec_all == 0.0:
                similarities.append(0.0)
                continue
            dot_product = sum(a * b for a, b in zip(vec, vector_1))
            similarity = dot_product / (norm_vec1 * norm_vec_all)
            similarities.append(similarity)
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

        for i in range(n):
            mean_vec1[i] /= len(vector_list_1)
            mean_vec2[i] /= len(vector_list_2)

        return VectorUtil.similarity(mean_vec1, mean_vec2)

    @staticmethod
    def compute_idf_weight_dict(total_num: int, number_dict: Dict[str, float]) -> Dict[str, float]:
        result: Dict[str, float] = {}
        index_2_key_map: Dict[int, str] = {}
        count_list: List[float] = []
        index = 0

        for key, count in number_dict.items():
            index_2_key_map[index] = key
            count_list.append(count)
            index += 1

        a = [0.0] * len(count_list)
        for i in range(len(count_list)):
            a[i] = math.log((total_num + 1.0) / (count_list[i] + 1.0))

        for i in range(len(a)):
            result[index_2_key_map[i]] = a[i]

        return result