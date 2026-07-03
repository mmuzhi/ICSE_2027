def kappa(test_data, k):
    data_mat = test_data
    total_observations = 0
    P0 = 0.0
    for i in range(k):
        P0 += data_mat[i][i]
    row_sums = [0] * k
    col_sums = [0] * k
    for i in range(k):
        for j in range(k):
            row_sums[i] += data_mat[i][j]
            col_sums[j] += data_mat[i][j]
            total_observations += data_mat[i][j]
    Pe = 0.0
    for i in range(k):
        Pe += col_sums[i] * row_sums[i]
    Pe = Pe / (total_observations ** 2)
    P0 = P0 / total_observations
    return (P0 - Pe) / (1 - Pe)

def fleiss_kappa(test_data, N, k, n):
    P = [0.0] * N
    total_sum = 0.0
    for i in range(N):
        row_total = 0
        temp = 0.0
        for j in range(k):
            row_total += test_data[i][j]
            temp += test_data[i][j] * test_data[i][j]
        temp -= n
        temp /= (n - 1) * n
        P[i] = temp
    P0 = sum(P) / N
    pj = [0.0] * k
    for j in range(k):
        for i in range(N):
            pj[j] += test_data[i][j]
    for j in range(k):
        pj[j] /= total_sum
    Pe = sum(p * p for p in pj)
    return (P0 - Pe) / (1 - Pe)