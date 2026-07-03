#include <iostream>
#include <vector>

using namespace std;

double kappa(const vector<vector<int>>& testData, int k) {
    double P0 = 0.0;
    for (int i = 0; i < k; i++) {
        P0 += testData[i][i];
    }

    vector<int> xsum(k, 0);
    vector<int> ysum(k, 0);
    int total = 0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            xsum[i] += testData[i][j];
            ysum[j] += testData[i][j];
            total += testData[i][j];
        }
    }

    double Pe = 0.0;
    for (int i = 0; i < k; i++) {
        Pe += static_cast<double>(xsum[i]) * ysum[i];
    }
    Pe = Pe / (static_cast<double>(total) * total);
    P0 = P0 / total;

    return (P0 - Pe) / (1 - Pe);
}

double fleissKappa(const vector<vector<int>>& testData, int N, int k, int n) {
    double total_sum = 0.0;
    vector<double> P(N);

    for (int i = 0; i < N; i++) {
        double squared_sum = 0.0;
        double row_sum = 0.0;
        for (int j = 0; j < k; j++) {
            int count = testData[i][j];
            row_sum += count;
            squared_sum += static_cast<double>(count) * count;
        }
        total_sum += row_sum;

        double temp = squared_sum - n;
        temp /= ((n - 1) * n);
        P[i] = temp;
    }

    double P0 = 0.0;
    for (double p : P) {
        P0 += p;
    }
    P0 /= N;

    vector<double> pj(k, 0.0);
    for (int j = 0; j < k; j++) {
        for (int i = 0; i < N; i++) {
            pj[j] += testData[i][j];
        }
        pj[j] /= total_sum;
    }

    double Pe = 0.0;
    for (double p : pj) {
        Pe += p * p;
    }

    return (P0 - Pe) / (1 - Pe);
}

int main() {
    cout << kappa({{2, 1, 1}, {1, 2, 1}, {1, 1, 2}}, 3) << endl;
    cout << fleissKappa({
        {0, 0, 0, 0, 14},
        {0, 2, 6, 4, 2},
        {0, 0, 3, 5, 6},
        {0, 3, 9, 2, 0},
        {2, 2, 8, 1, 1},
        {7, 7, 0, 0, 0},
        {3, 2, 6, 3, 0},
        {2, 5, 3, 2, 2},
        {6, 5, 2, 1, 0},
        {0, 2, 2, 3, 7}
    }, 10, 5, 14) << endl;

    return 0;
}