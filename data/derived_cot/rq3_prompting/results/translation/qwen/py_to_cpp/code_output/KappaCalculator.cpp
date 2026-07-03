#include <vector>
#include <cmath>
#include <iostream>

class KappaCalculator {
public:
    static double kappa(const std::vector<std::vector<double>>& testData, int k) {
        double P0 = 0.0;
        for (int i = 0; i < k; i++) {
            P0 += testData[i][i];
        }

        double sum = 0.0;
        for (const auto& row : testData) {
            for (double val : row) {
                sum += val;
            }
        }

        std::vector<double> xsum(k, 0.0);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                xsum[i] += testData[i][j];
            }
        }

        std::vector<double> ysum(k, 0.0);
        for (int j = 0; j < k; j++) {
            for (int i = 0; i < k; i++) {
                ysum[j] += testData[i][j];
            }
        }

        double Pe = 0.0;
        for (int i = 0; i < k; i++) {
            Pe += ysum[i] * xsum[i];
        }
        Pe = Pe / (sum * sum);

        P0 = P0 / sum;

        return (P0 - Pe) / (1 - Pe);
    }

    static double fleissKappa(const std::vector<std::vector<double>>& testData, int N, int k, int n) {
        double sum = 0.0;
        double P0 = 0.0;

        for (int i = 0; i < N; i++) {
            double temp = 0.0;
            for (int j = 0; j < k; j++) {
                sum += testData[i][j];
                temp += testData[i][j] * testData[i][j];
            }
            temp = (temp - n) / ((n - 1) * n);
            P0 += temp;
        }
        P0 /= N;

        std::vector<double> ysum(k, 0.0);
        for (int j = 0; j < k; j++) {
            for (int i = 0; i < N; i++) {
                ysum[j] += testData[i][j];
            }
        }

        for (int j = 0; j < k; j++) {
            ysum[j] = std::pow(ysum[j] / sum, 2);
        }

        double Pe = 0.0;
        for (int i = 0; i < k; i++) {
            Pe += ysum[i];
        }

        return (P0 - Pe) / (1 - Pe);
    }
};

int main() {
    // Example usage of kappa
    std::vector<std::vector<double>> testData = {{2, 1, 1}, {1, 2, 1}, {1, 1, 2}};
    std::cout << "Cohen's kappa: " << KappaCalculator::kappa(testData, 3) << std::endl;

    // Example usage of fleissKappa
    std::vector<std::vector<double>> testData2 = {
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
    std::cout << "Fleiss' kappa: " << KappaCalculator::fleissKappa(testData2, 10, 5, 14) << std::endl;

    return 0;
}