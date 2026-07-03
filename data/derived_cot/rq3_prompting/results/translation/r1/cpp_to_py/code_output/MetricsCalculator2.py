from typing import List, Tuple, Dict, Any

class MetricsCalculator2:
    @staticmethod
    def mrr(data: List[Tuple[List[int], int]]) -> Tuple[float, List[float]]:
        if not data:
            return (0.0, [0.0])

        sum_mrr = 0.0
        individual_mrr = []

        for vec, k in data:
            if k <= 0 or not vec:
                individual_mrr.append(0.0)
            else:
                # find first occurrence of 1
                mrr_val = 0.0
                for idx, val in enumerate(vec):
                    if val == 1:
                        mrr_val = 1.0 / (idx + 1)
                        break
                individual_mrr.append(mrr_val)
                sum_mrr += mrr_val

        average_mrr = sum_mrr / len(data) if data else 0.0
        return (average_mrr, individual_mrr)

    @staticmethod
    def map(data: List[Tuple[List[int], int]]) -> Tuple[float, List[float]]:
        if not data:
            return (0.0, [0.0])

        separate_result = []

        for sub_list, total_num in data:
            if total_num == 0:
                separate_result.append(0.0)
                continue

            length = len(sub_list)
            # ranking_array[i] = 1.0 / (i+1)
            ranking_array = [1.0 / (i + 1) for i in range(length)]

            right_ranking_list = [0.0] * length
            count = 1
            for i, val in enumerate(sub_list):
                if val != 0:
                    right_ranking_list[i] = float(count)
                    count += 1

            ap = sum(r * rank for r, rank in zip(right_ranking_list, ranking_array)) / total_num
            separate_result.append(ap)

        mean_ap = sum(separate_result) / len(separate_result) if separate_result else 0.0
        return (mean_ap, separate_result)