import numpy as np

def kappa(test_data, k):
    data = np.array(test_data)
    n_subjects = data.shape[0]
    if data.shape[1] != k:
        raise ValueError("The number of columns in test_data must be equal to k")
    
    P0 = np.sum(np.diag(data))
    
    xsum = data.sum(axis=1)
    ysum = data.sum(axis=0)
    total_sum = data.sum()
    
    dot_product = np.dot(ysum, xsum)
    Pe = dot_product / (total_sum * total_sum)
    
    P0 /= total_sum
    
    return (P0 - Pe) / (1 - Pe)

def fleiss_kappa(test_data, N, k, n):
    data = np.array(test_data)
    if data.shape[0] != N or data.shape[1] != k:
        raise ValueError("The data dimensions must be N x k")
    
    P0 = 0.0
    total_sum = 0.0
    
    for i in range(N):
        row = data[i]
        row_sum = np.sum(row)
        total_sum += row_sum
        
        temp = np.sum(np.square(row))
        temp -= n
        temp /= (n - 1) * n
        P0 += temp
    
    P0 /= N
    
    ysum = data.sum(axis=0)
    ysum = ysum / total_sum
    ysum = np.square(ysum)
    Pe = np.sum(ysum)
    
    return (P0 - Pe) / (1 - Pe)