def kappa(testData, k):
    dataMat = testData
    P0 = 0.0
    for i in range(k):
        P0 += dataMat[i][i] * 1.0
    
    xsum = [0] * k
    ysum = [0] * k
    total_sum = 0
    for i in range(k):
        for j in range(k):
            xsum[i] += dataMat[i][j]
            ysum[j] += dataMat[i][j]
            total_sum += dataMat[i][j]
            
    Pe = 0.0
    for i in range(k):
        Pe += ysum[i] * xsum[i]
    Pe = Pe / (total_sum * total_sum)
    
    P0 = P0 / total_sum
    return (P0 - Pe) / (1 - Pe)

def fleissKappa(testData, N, k, n):
    dataMat = testData
    P = [0.0] * N
    total_sum_val = 0.0
    
    for i in range(N):
        temp = 0.0
        for j in range(k):
            total_sum_val += dataMat[i][j]
            temp += dataMat[i][j] * dataMat[i][j]
        temp -= n
        temp /= (n - 1) * n
        P[i] = temp
        
    P0 = sum(P) / N
    
    pj = [0.0] * k
    for j in range(k):
        for i in range(N):
            pj[j] += dataMat[i][j]
        pj[j] /= total_sum_val
        
    Pe = 0.0
    for j in range(k):
        Pe += pj[j] * pj[j]
        
    return (P0 - Pe) / (1 - Pe)

if __name__ == '__main__':
    print(kappa([[2, 1, 1], [1, 2, 1], [1, 1, 2]], 3))  # Expected: 0.25
    data = [
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
    print(fleissKappa(data, 10, 5, 14))