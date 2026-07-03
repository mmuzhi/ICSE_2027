#include <vector>
#include <numeric>
#include <cmath>

double kappa(const std::vector<std::vector<int>>& testData, int k) {
    double P0 = 0.0;
    for (int i = 0; i < k; i++) {
        P0 += static_cast<double>(testData[i][i]);
    }

    int total = 0;
    std::vector<int> xsum(k, 0);
    std::vector<int> ysum(k, 0);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            xsum[i] += testData[i][j];
            ysum[j] += testData[i][j];
            total += testData[i][j];
        }
    }

    double Pe = 0.0;
    for (int i = 0; i < k; i++) {
        Pe += static_cast<double>(ysum[i]) * static_cast<double>(xsum[i]);
    }
    Pe /= (total * total);
    P0 /= total;
    return (P0 - Pe) / (1 - Pe);
}

double fleissKappa(const std::vector<std::vector<int>>& testData, int N, int k, int n) {
    std::vector<double> P(N, 0.0);
    double totalSum = 0.0;

    for (int i = 0; i < N; i++) {
        double temp = 0.0;
        for (int j = 0; j < k; j++) {
            totalSum += testData[i][j];
            temp += static_cast<double>(testData[i][j]) * static_cast<double>(testData[i][j]);
        }
        temp -= static_cast<double>(n);
        temp /= static_cast<double>((n - 1) * n);
        P[i] = temp;
    }

    double P0 = std::accumulate(P.begin(), P.end(), 0.0) / N;

    std::vector<double> pj(k, 0.0);
    for (int j = 0; j < k; j++) {
        for (int i = 0; i < N; i++) {
            pj[j] += testData[i][j];
        }
        pj[j] /= totalSum;
    }

    double Pe = 0.0;
    for (int j = 0; j < k; j++) {
        Pe += pj[j] * pj[j];
    }
    return (P0 - Pe) / (1 - Pe);
}