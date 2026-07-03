class MetricsCalculator2:
    @staticmethod
    def mrr(data):
        if not data:
            return (0.0, [0.0])
        
        individual_mrr = []
        total_mrr = 0.0
        
        for item in data:
            vec, k = item
            if k <= 0 or not vec:
                individual_mrr.append(0.0)
            else:
                try:
                    idx = vec.index(1)
                    mrr_val = 1.0 / (idx + 1)
                except ValueError:
                    mrr_val = 0.0
                individual_mrr.append(mrr_val)
                total_mrr += mrr_val
        
        average_mrr = total_mrr / len(data)
        return (average_mrr, individual_mrr)
    
    @staticmethod
    def map(data):
        if not data:
            return (0.0, [0.0])
        
        separate_result = []
        
        for item in data:
            sub_list, total_num = item
            n = len(sub_list)
            if total_num == 0:
                separate_result.append(0.0)
                continue
            
            ranking_array = [1.0 / (i + 1) for i in range(n)]
            right_ranking_list = [0.0] * n
            count = 1
            for i in range(n):
                if sub_list[i] != 0:
                    right_ranking_list[i] = count
                    count += 1
            
            inner_prod = 0.0
            for i in range(n):
                inner_prod += right_ranking_list[i] * ranking_array[i]
            
            ap = inner_prod / total_num
            separate_result.append(ap)
        
        mean_ap = sum(separate_result) / len(separate_result)
        return (mean_ap, separate_result)