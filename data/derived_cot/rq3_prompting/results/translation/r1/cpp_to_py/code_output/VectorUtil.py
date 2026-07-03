import math


class VectorUtil:
    """Translation of the C++ VectorUtil class with fixed-size array templates replaced by dynamic lists."""

    @staticmethod
    def _norm(vec):
        """Compute L2 norm."""
        return math.sqrt(sum(x * x for x in vec))

    @staticmethod
    def _normalize(vec):
        """Return normalized vector (zero vector if norm is zero)."""
        n = VectorUtil._norm(vec)
        if n == 0.0:
            return [0.0] * len(vec)
        return [x / n for x in vec]

    @staticmethod
    def similarity(vector_1, vector_2):
        """Cosine similarity of two vectors (assumed same length)."""
        norm_vec1 = VectorUtil._normalize(vector_1)
        norm_vec2 = VectorUtil._normalize(vector_2)
        return sum(a * b for a, b in zip(norm_vec1, norm_vec2))

    @staticmethod
    def cosine_similarities(vector_1, vectors_all):
        """List of cosine similarities between vector_1 and each vector in vectors_all."""
        norm1 = VectorUtil._norm(vector_1)
        similarities = []
        for vec in vectors_all:
            norm_all = VectorUtil._norm(vec)
            if norm_all == 0.0:
                similarities.append(0.0)
                continue
            dot = sum(a * b for a, b in zip(vec, vector_1))
            similarities.append(dot / (norm1 * norm_all))
        return similarities

    @staticmethod
    def n_similarity(vector_list_1, vector_list_2):
        """Cosine similarity between the mean vectors of two lists of vectors."""
        if not vector_list_1 or not vector_list_2:
            raise ValueError("At least one of the lists is empty.")
        n = len(vector_list_1[0])
        mean1 = [0.0] * n
        mean2 = [0.0] * n
        for vec in vector_list_1:
            for i in range(n):
                mean1[i] += vec[i]
        for vec in vector_list_2:
            for i in range(n):
                mean2[i] += vec[i]
        for i in range(n):
            mean1[i] /= len(vector_list_1)
            mean2[i] /= len(vector_list_2)
        return VectorUtil.similarity(mean1, mean2)

    @staticmethod
    def compute_idf_weight_dict(total_num, number_dict):
        """Compute IDF weight dict: log((total_num+1)/(count+1))."""
        index_2_key_map = {}
        count_list = []
        index = 0
        for key, count in number_dict.items():
            index_2_key_map[index] = key
            count_list.append(count)
            index += 1
        a = [math.log((total_num + 1.0) / (c + 1.0)) for c in count_list]
        return {index_2_key_map[i]: a[i] for i in range(len(a))}