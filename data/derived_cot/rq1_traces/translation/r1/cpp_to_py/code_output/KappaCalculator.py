import numpy as np

class KappaCalculator:
    @staticmethod
    def kappa(testData, k):
        n_rows = len(testData)
        data_mat = np.zeros((n_rows, k))
        for i in range(n_rows):
            for j in range(k):
                data_mat[i, j] = testData[i][j]
        
        total_sum = np.sum(data_mat)
        P0 = 0.0
        for i in range(k):
            P0 += data_mat[i, i]
        
        row_sums = np.sum(data_mat, axis=1)
        col_sums = np.sum(data_mat, axis=0)
        Pe = np.dot(row_sums, col_sums) / (total_sum * total_sum)
        P0 /= total_sum
        
        cohens_coefficient = (P0 - Pe) / (1 - Pe)
        return cohens_coefficient

    @staticmethod
    def fleiss_kappa(testData, N, k, n):
        n_rows = len(testData)
        data_mat = np.zeros((n_rows, k))
        for i in range(n_rows):
            for j in range(k):
                data_mat[i, j] = testData[i][j]
        
        total_sum = 0.0
        P0 = 0.0
        for i in range(N):
            row = data_mat[i]
            row_sum = np.sum(row)
            total_sum += row_sum
            sq_sum = np.sum(row ** 2)
            temp = sq_sum - n
            temp /= (n - 1) * n
            P0 += temp
        
        P0 /= N
        col_sums = np.sum(data_mat, axis=0)
        col_prop = col_sums / total_sum
        col_prop_sq = col_prop ** 2
        Pe = np.sum(col_prop_sq)
        
        ans = (P0 - Pe) / (1 - Pe)
        return ans