import math

class VectorUtil:
    
    @staticmethod
    def norm(vec):
        sum_val = 0.0
        for val in vec:
            sum_val += val * val
        return math.sqrt(sum_val)

    @staticmethod
    def normalize(vec):
        vec_norm = VectorUtil.norm(vec)
        if vec_norm == 0.0:
            return [0.0] * len(vec)
        return [v / vec_norm for v in vec]

    @staticmethod
    def similarity(vector_1, vector_2):
        norm_vec1 = VectorUtil.normalize(vector_1)
        norm_vec2 = VectorUtil.normalize(vector_2)
        dot_product = 0.0
        for v1, v2 in zip(norm_vec1, norm_vec2):
            dot_product += v1 * v2
        return dot_product

    @staticmethod
    def cosine_similarities(vector_1, vectors_all):
        similarities = []
        norm_vec1 = VectorUtil.norm(vector_1)

        for vec in vectors_all:
            norm_vec_all = VectorUtil.norm(vec)
            if norm_vec_all == 0.0:
                similarities.append(0.0)
                continue
            
            dot_product = 0.0
            for v1, v2 in zip(vector_1, vec):
                dot_product += v1 * v2
            
            # In C++, float division by zero (0.0 / 0.0) results in NaN, 
            # whereas Python raises a ZeroDivisionError. We replicate the C++ 
            # behavior here. If norm_vec1 is 0.0, vector_1 is all zeros, 
            # making dot_product 0.0, which yields NaN.
            if norm_vec1 == 0.0:
                similarity = float('nan')
            else:
                similarity = dot_product / (norm_vec1 * norm_vec_all)
                
            similarities.append(similarity)
            
        return similarities

    @staticmethod
    def n_similarity(vector_list_1, vector_list_2):
        if not vector_list_1 or not vector_list_2:
            raise ValueError("At least one of the lists is empty.")

        # Determine N from the first vector (C++ templates enforce uniform length)
        n = len(vector_list_1[0])
        
        mean_vec1 = [0.0] * n
        mean_vec2 = [0.0] * n

        for vec in vector_list_1:
            for i in range(n):
                mean_vec1[i] += vec[i]

        for vec in vector_list_2:
            for i in range(n):
                mean_vec2[i] += vec[i]

        len1 = len(vector_list_1)
        len2 = len(vector_list_2)

        for i in range(n):
            mean_vec1[i] /= len1
            mean_vec2[i] /= len2

        return VectorUtil.similarity(mean_vec1, mean_vec2)

    @staticmethod
    def compute_idf_weight_dict(total_num, number_dict):
        result = {}
        for key, count in number_dict.items():
            result[key] = math.log((total_num + 1.0) / (count + 1.0))
        return result