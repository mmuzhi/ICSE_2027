import numpy as np

class KappaCalculator:
    @staticmethod
    def kappa(testData, k):
        # Build matrix: rows = number of rows in testData, columns = k (only first k columns of each row)
        dataMat = np.array([row[:k] for row in testData], dtype=float)
        # Diagonal sum (square matrix assumed: rows >= k; otherwise out-of-bounds)
        P0 = np.diag(dataMat[:k, :k]).sum()
        xsum = dataMat.sum(axis=1)  # row sums (length = number of rows)
        ysum = dataMat.sum(axis=0)  # column sums (length = k)
        total = dataMat.sum()
        Pe = np.dot(ysum, xsum) / (total * total)
        P0 /= total
        return (P0 - Pe) / (1 - Pe)

    @staticmethod
    def fleiss_kappa(testData, N, k, n):
        # Build matrix: rows = N (first N rows), columns = k (first k columns)
        dataMat = np.array([row[:k] for row in testData[:N]], dtype=float)
        total = dataMat.sum()
        P0 = 0.0
        for i in range(N):
            temp = 0.0
            for j in range(k):
                temp += dataMat[i, j] ** 2
            temp = (temp - n) / ((n - 1) * n)
            P0 += temp
        P0 /= N
        ysum = dataMat.sum(axis=0)
        ysum /= total
        Pe = (ysum ** 2).sum()
        return (P0 - Pe) / (1 - Pe)