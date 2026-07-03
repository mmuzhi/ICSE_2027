class KappaCalculator:

    @staticmethod
    def kappa(testData, k):
        # Convert the input to a list of lists if needed (though it should be already)
        # Calculate P0: sum of diagonal elements
        P0 = 0.0
        for i in range(k):
            P0 += testData[i][i]
        
        # Calculate row and column sums
        xsum = [0] * k
        ysum = [0] * k
        total_count = 0
        
        for i in range(k):
            for j in range(k):
                xsum[i] += testData[i][j]
                ysum[j] += testData[i][j]
                total_count += testData[i][j]
        
        # Calculate expected agreement (Pe)
        Pe = 0.0
        for i in range(k):
            Pe += ysum[i] * xsum[i]
        Pe = Pe / (total_count ** 2)
        
        P0 = P0 / total_count
        
        return (P0 - Pe) / (1 - Pe)

    @staticmethod
    def fleissKappa(testData, N, k, n):
        # For each subject, compute the variance of ratings
        P = [0.0] * N
        total_count = N * n  # Total number of items
        
        for i in range(N):
            row_sum_sq = 0
            for j in range(k):
                row_sum_sq += testData[i][j] ** 2
            row_sum_sq -= n
            P[i] = row_sum_sq / ((n - 1) * n)
        
        # Calculate P0: average of P
        P0 = sum(P) / N
        
        # Calculate expected agreement (Pe)
        pj = [0.0] * k
        for j in range(k):
            for i in range(N):
                pj[j] += testData[i][j]
        for j in range(k):
            pj[j] /= total_count
        
        Pe = sum(p * p for p in pj)
        
        return (P0 - Pe) / (1 - Pe)

    @staticmethod
    def main():
        # Example usage
        print(KappaCalculator.kappa([[2, 1, 1], [1, 2, 1], [1, 1, 2]], 3))  # Expected 0.25
        matrix = [
            [0, 0, 0, 0, 14],
            [0, 2, 6, 4, 2],
            [0, 0, 3, 5, 6],
            [0, 3, 9, 2, 0],
            [2, 2, 8, 1, 1],
            [7, 7, 0, 0, 0],
            [3, 2, 6, 3, 0],
            [2, 5, 3, 2, 2],
            [6, 5, 2, 1, 0],
            [0, 2, 2, 3, 7]
        ]
        print(KappaCalculator.fleissKappa(matrix, 10, 5, 14))