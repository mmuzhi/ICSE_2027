class MetricsCalculator2:
    @staticmethod
    def _calculate_mrr(vec, k):
        try:
            idx = vec.index(1)
        except ValueError:
            return 0.0
        return 1.0 / (idx + 1)

    @staticmethod
    def _calculate_map(vec, k):
        s = 0.0
        count = 0
        for i in range(len(vec)):
            if vec[i] == 1:
                count += 1
                s += count / (i + 1)
        return s / count if count else 0.0

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
                mrr_val = MetricsCalculator2._calculate_mrr(vec, k)
                individual_mrr.append(mrr_val)
                sum_mrr += mrr_val

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

            length = len(sub_list)
            ranking_array = [1.0 / (i + 1) for i in range(length)]

            right_ranking_list = [0.0] * length
            count = 1

            for i in range(length):
                if sub_list[i] != 0:
                    right_ranking_list[i] = count
                    count += 1

            ap = sum(a * b for a, b in zip(right_ranking_list, ranking_array)) / total_num
            separate_result.append(ap)

        mean_ap = sum(separate_result) / len(separate_result)
        return (mean_ap, separate_result)