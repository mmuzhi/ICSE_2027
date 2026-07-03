#include <vector>
#include <cmath>

class KappaCalculator {
public:
    static double kappa(const std::vector<std::vector<double>>& testData, int k) {
        double P0 = 0.0;
        std::vector<double> xsum(k, 0.0);
        std::vector<double> ysum(k, 0.0);
        double total = 0.0;

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                xsum[i] += testData[i][j];
                ysum[j] += testData[i][j];
                total += testData[i][j];
            }
            P0 += testData[i][i];
        }

        double Pe = 0.0;
        for (int i = 0; i < k; i++) {
            Pe += xsum[i] * ysum[i];
        }
        Pe = Pe / total / total;
        P0 = P0 / total;

        double cohens_coefficient = (P0 - Pe) / (1.0 - Pe);
        return cohens_coefficient;
    }

    static double fleiss_kappa(const std::vector<std::vector<double>>& testData, int N, int k, int n) {
        double sum = 0.0;
        double P0 = 0.0;

        for (int i = 0; i < N; i++) {
            double temp = 0.0;
            for (int j = 0; j < k; j++) {
                sum += testData[i][j];
                temp += 1.0 * testData[i][j] * testData[i][j];
            }
            temp -= n;
            temp /= (n - 1.0) * n;
            P0 += temp;
        }
        P0 = 1.0 * P0 / N;

        std::vector<double> ysum(k, 0.0);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < k; j++) {
                ysum[j] += testData[i][j];
            }
        }

        double Pe = 0.0;
        for (int i = 0; i < k; i++) {
            ysum[i] = std::pow(ysum[i] / sum, 2);
            Pe += ysum[i];
        }

        double ans = (P0 - Pe) / (1.0 - Pe);
        return ans;
    }
};