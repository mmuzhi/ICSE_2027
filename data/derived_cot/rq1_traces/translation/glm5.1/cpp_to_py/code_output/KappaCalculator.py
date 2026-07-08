import numpy as np

class KappaCalculator:
    @staticmethod
    def kappa(testData, k):
        rows = len(testData)
        dataMat = np.zeros((rows, k))
        
        for i in range(rows):
            for j in range(k):
                dataMat[i, j] = testData[i][j]
                
        P0 = 0.0
        for i in range(k):
            P0 += dataMat[i, i]
            
        xsum = np.sum(dataMat, axis=1)
        ysum = np.sum(dataMat, axis=0)
        total_sum = np.sum(dataMat)
        
        Pe = np.dot(ysum, xsum) / (total_sum * total_sum)
        P0 /= total_sum
        
        cohens_coefficient = (P0 - Pe) / (1 - Pe)
        return cohens_coefficient

    @staticmethod
    def fleiss_kappa(testData, N, k, n):
        rows = len(testData)
        dataMat = np.zeros((rows, k))
        
        for i in range(rows):
            for j in range(k):
                dataMat[i, j] = testData[i][j]
                
        total_sum = 0.0
        P0 = 0.0
        
        for i in range(N):
            temp = 0.0
            for j in range(k):
                total_sum += dataMat[i, j]
                temp += dataMat[i, j] ** 2
            temp -= n
            temp /= (n - 1) * n
            P0 += temp
            
        P0 /= N
        
        ysum = np.sum(dataMat, axis=0)
        ysum = ysum / total_sum
        ysum = ysum ** 2
        
        Pe = np.sum(ysum)
        
        ans = (P0 - Pe) / (1 - Pe)
        return ans