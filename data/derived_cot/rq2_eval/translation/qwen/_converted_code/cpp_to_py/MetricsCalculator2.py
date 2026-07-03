from typing import List, Tuple

class MetricsCalculator2:
    @staticmethod
    def mrr(data: List[Tuple[List[int], int]]) -> Tuple[float, List[float]]:
        if not data:
            return (0.0, [0.0])
        
        total_sum = 0.0
        individual_scores = []
        
        for vec, k in data:
            if k <= 0 or not vec:
                individual_scores.append(0.0)
            else:
                try:
                    idx = vec.index(1)
                    score = 1.0 / (idx + 1)
                    individual_scores.append(score)
                    total_sum += score
                except ValueError:
                    individual_scores.append(0.0)
        
        average_score = total_sum / len(data) if data else 0.0
        return (average_score, individual_scores)

    @staticmethod
    def map(data: List[Tuple[List[int], int]]) -> Tuple[float, List[float]]:
        if not data:
            return (0.0, [0.0])
        
        individual_scores = []
        
        for sub_list, total_num in data:
            if total_num == 0:
                individual_scores.append(0.0)
                continue
            
            n = len(sub_list)
            if n == 0:
                individual_scores.append(0.0)
                continue
            
            reciprocal_ranks = [1.0 / i for i in range(1, n+1)]
            count = 1
            right_ranking_list = []
            for item in sub_list:
                if item != 0:
                    right_ranking_list.append(count)
                    count += 1
                else:
                    right_ranking_list.append(0.0)
            
            weighted_sum = sum(a * b for a, b in zip(right_ranking_list, reciprocal_ranks))
            ap = weighted_sum / total_num
            individual_scores.append(ap)
        
        mean_ap = sum(individual_scores) / len(individual_scores) if individual_scores else 0.0
        return (mean_ap, individual_scores)