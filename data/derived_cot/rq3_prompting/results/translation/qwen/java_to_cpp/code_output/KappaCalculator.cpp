#include <iostream>
#include <vector>
#include <iomanip>

class KappaCalculator {

public:
    static double kappa(const std::vector<std::vector<int>>& dataMat, int k) {
        double P0 = 0.0;
        for (int i = 0; i < k; i++) {
            P0 += static_cast<double>(dataMat[i][i]);
        }

        std::vector<int> xsum(k, 0);
        std::vector<int> ysum(k, 0);
        int sum = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                xsum[i] += dataMat[i][j];
                ysum[j] += dataMat[i][j];
                sum += dataMat[i][j];
            }
        }

        double Pe = 0.0;
        for (int i = 0; i < k; i++) {
            Pe += static_cast<double>(ysum[i]) * static_cast<double>(xsum[i]);
        }
        Pe = Pe / (static_cast<double>(sum) * static_cast<double>(sum));

        P0 = P0 / static_cast<double>(sum);

        return (P0 - Pe) / (1 - Pe);
    }

    static double fleissKappa(const std::vector<std::vector<int>>& dataMat, int N, int k, int n) {
        std::vector<double> P(N);
        double totalSum = 0.0;

        for (int i = 0; i < N; i++) {
            double temp = 0.0;
            for (int j = 0; j < k; j++) {
                totalSum += dataMat[i][j];
                temp += static_cast<double>(dataMat[i][j]) * static_cast<double>(dataMat[i][j]);
            }
            temp -= n;
            temp /= (n - 1) * static_cast<double>(n);
            P[i] = temp;
        }

        double P0 = 0.0;
        for (double p : P) {
            P0 += p;
        }
        P0 /= static_cast<double>(N);

        std::vector<double> pj(k, 0.0);
        for (int j = 0; j < k; j++) {
            for (int i = 0; i < N; i++) {
                pj[j] += dataMat[i][j];
            }
            pj[j] /= static_cast<double>(totalSum);
        }

        double Pe = 0.0;
        for (int j = 0; j < k; j++) {
            Pe += pj[j] * pj[j];
        }

        return (P0 - Pe) / (1 - Pe);
    }

};

int main() {
    std::vector<std::vector<int>> data1 = {{2, 1, 1}, {1, 2, 1}, {1, 1, 2}};
    std::cout << std::fixed << std::setprecision(2) << KappaCalculator::kappa(data1, 3) << std::endl;

    std::vector<std::vector<int>> data2 = {
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
    };
    std::cout << std::fixed << std::setprecision(10) << KappaCalculator::fleissKappa(data2, 10, 5, 14) << std::endl;

    return 0;
}