#include <vector>
#include <cstddef>

class KappaCalculator {
public:
    static double kappa(const std::vector<std::vector<int>>& testData, int k) {
        // Convert to double vectors for arithmetic
        std::vector<std::vector<double>> data(k, std::vector<double>(k));
        double sum = 0.0;
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                data[i][j] = static_cast<double>(testData[i][j]);
                sum += data[i][j];
            }
        }

        // Diagonal sum (P0)
        double P0 = 0.0;
        for (int i = 0; i < k; ++i) {
            P0 += data[i][i];
        }
        double P0_ratio = P0 / sum;

        // Row sums and column sums
        std::vector<double> rowSums(k, 0.0);
        std::vector<double> colSums(k, 0.0);
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                rowSums[i] += data[i][j];
                colSums[j] += data[i][j];
            }
        }

        // Pe = (colSums dot rowSums) / (sum * sum)
        double Pe = 0.0;
        for (int i = 0; i < k; ++i) {
            Pe += colSums[i] * rowSums[i];
        }
        Pe /= (sum * sum);

        double kappa = (P0_ratio - Pe) / (1.0 - Pe);
        return kappa;
    }

    static double fleiss_kappa(const std::vector<std::vector<int>>& testData, int N, int k, int n) {
        // Convert to double matrix
        std::vector<std::vector<double>> data(N, std::vector<double>(k));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < k; ++j) {
                data[i][j] = static_cast<double>(testData[i][j]);
            }
        }

        double totalSum = 0.0;
        double P0 = 0.0;
        std::vector<double> colSums(k, 0.0);

        for (int i = 0; i < N; ++i) {
            double temp = 0.0;
            for (int j = 0; j < k; ++j) {
                double val = data[i][j];
                totalSum += val;
                temp += val * val;
                colSums[j] += val;
            }
            temp -= static_cast<double>(n);
            temp /= static_cast<double>((n - 1) * n);
            P0 += temp;
        }
        P0 /= static_cast<double>(N);

        double Pe = 0.0;
        for (int j = 0; j < k; ++j) {
            double pj = colSums[j] / totalSum;
            Pe += pj * pj;
        }

        double ans = (P0 - Pe) / (1.0 - Pe);
        return ans;
    }
};