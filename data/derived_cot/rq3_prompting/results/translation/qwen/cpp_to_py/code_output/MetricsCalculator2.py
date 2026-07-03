class MetricsCalculator2:
    @staticmethod
    def mrr(data):
        if not data:
            return (0.0, [0.0])
        
        sum_mrr = 0.0
        individual_mrr = []
        
        for vec, k in data:
            if k <= 0 or not vec:
                individual_mrr.append(0.0)
            else:
                try:
                    pos = vec.index(1)
                    mrr_val = 1.0 / (pos + 1)
                    individual_mrr.append(mrr_val)
                    sum_mrr += mrr_val
                except ValueError:
                    individual_mrr.append(0.0)
        
        average_mrr = sum_mrr / len(data) if data else 0.0
        return (average_mrr, individual_mrr)
    
    @staticmethod
    def map(data):
        if not data:
            return (0.0, [0.0])
        
        separate_result = []
        
        for sub_list, total_num in data:
            if total_num == 0:
                separate_result.append(0.0)
                continue
            
            n = len(sub_list)
            ranking_array = [1.0 / (i + 1) for i in range(n)]
            right_ranking_list = [0.0] * n
            count = 1
            
            for i in range(n):
                if sub_list[i] != 0:
                    right_ranking_list[i] = count
                    count += 1
            
            ap = sum(x * y for x, y in zip(right_ranking_list, ranking_array)) / total_num
            separate_result.append(ap)
        
        mean_ap = sum(separate_result) / len(separate_result) if separate_result else 0.0
        return (mean_ap, separate_result)