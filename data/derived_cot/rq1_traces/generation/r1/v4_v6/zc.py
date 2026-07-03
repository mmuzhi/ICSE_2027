MOD = 998244353

def main():
    import sys
    data = sys.stdin.read().split()
    n = int(data[0])
    q = int(data[1])
    A = [0] * (n + 1)
    for i in range(2, n + 1):
        A[i] = int(data[i - 1])
    
    fac = 1
    for i in range(1, n):
        fac = (fac * i) % MOD

    inv = [0] * (n + 1)
    for i in range(1, n + 1):
        inv[i] = pow(i, MOD - 2, MOD)

    sum1 = [0] * (n + 1)
    for i in range(2, n + 1):
        sum1[i] = (sum1[i - 1] + A[i] * inv[i]) % MOD

    sum2 = [0] * (n + 1)
    for i in range(2, n + 1):
        sum2[i] = (sum2[i - 1] + A[i] * pow(i, MOD - 2, MOD) * pow(i, MOD - 2, MOD)) % MOD

    out_lines = []
    index = n
    for _ in range(q):
        u = int(data[index])
        v = int(data[index + 1])
        index += 2
        if u > v:
            u, v = v, u
        dist_u = sum1[u]
        dist_v = sum1[v]
        dist_lca = sum2[u]
        res = (dist_u + dist_v - 2 * dist_lca) % MOD
        res = (res * fac) % MOD
        if res < 0:
            res += MOD
        out_lines.append(str(res))
    
    print("\n".join(out_lines))

if __name__ == '__main__':
    main()