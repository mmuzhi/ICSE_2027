#include <vector>
#include <iostream>

class KappaCalculator {
public:
    static double kappa(std::vector<std::vector<int>> const& testData, int k) {
        double total_sum = 0.0;
        double diag_sum = 0.0;
        std::vector<double> row_sums(k, 0.0);
        std::vector<double> col_sums(k, 0.0);

        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                int value = testData[i][j];
                total_sum += value;
                row_sums[i] += value;
                col_sums[j] += value;
                if (i == j) {
                    diag_sum += value;
                }
            }
        }

        double P0 = diag_sum / total_sum;
        double dot_product = 0.0;
        for (int i = 0; i < k; ++i) {
            dot_product += row_sums[i] * col_sums[i];
        }
        double Pe = dot_product / (total_sum * total_sum);

        if (Pe == 1.0 && P0 == 1.0) {
            return 0.0 / 0.0; // NaN
        }

        return (P0 - Pe) / (1 - Pe);
    }

    static double fleiss_kappa(std::vector<std::vector<int>> const& testData, int N, int k, int n) {
        double total_sum = 0.0;
        std::vector<double> col_sums(k, 0.0);
        double P0 = 0.0;

        for (int i = 0; i < N; ++i) {
            double row_sum_sq = 0.0;
            for (int j = 0; j < k; ++j) {
                int value = testData[i][j];
                total_sum += value;
                col_sums[j] += value;
                row_sum_sq += static_cast<double>(value) * value;
            }
            double temp = (row_sum_sq - n) / (n * (n - 1));
            P0 += temp;
        }
        P0 /= N;

        double Pe = 0.0;
        for (int j = 0; j < k; ++j) {
            double p_j = col_sums[j] / total_sum;
            Pe += p_j * p_j;
        }

        if (Pe == 1.0 && P0 == 1.0) {
            return 0.0 / 0.0; // NaN
        }

        return (P0 - Pe) / (1 - Pe);
    }
};