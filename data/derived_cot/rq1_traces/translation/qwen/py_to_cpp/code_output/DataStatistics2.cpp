#include <vector>
#include <numeric>
#include <cmath>
#include <limits>

class DataStatistics2 {
private:
    std::vector<std::vector<double>> data2D;

    std::vector<double> getFlattenedData() {
        std::vector<double> flattened;
        for (const auto& row : data2D) {
            flattened.insert(flattened.end(), row.begin(), row.end());
        }
        return flattened;
    }

    std::vector<std::vector<double>> computeCorrelationMatrix() {
        if (data2D.empty()) {
            return std::vector<std::vector<double>>();
        }
        size_t n = data2D.size();
        size_t m = data2D[0].size();

        std::vector<double> means(m, 0.0);
        for (size_t j = 0; j < m; ++j) {
            for (size_t i = 0; i < n; ++i) {
                means[j] += data2D[i][j];
            }
            means[j] /= n;
        }

        std::vector<std::vector<double>> covMatrix(m, std::vector<double>(m, 0.0));
        for (size_t j = 0; j < m; ++j) {
            for (size_t k = 0; k < m; ++k) {
                for (size_t i = 0; i < n; ++i) {
                    covMatrix[j][k] += (data2D[i][j] - means[j]) * (data2D[i][k] - means[k]);
                }
                covMatrix[j][k] /= n;
            }
        }

        std::vector<double> stdDevs(m, 0.0);
        for (size_t j = 0; j < m; ++j) {
            stdDevs[j] = std::sqrt(covMatrix[j][j]);
        }

        std::vector<std::vector<double>> corrMatrix(m, std::vector<double>(m, 0.0));
        for (size_t j = 0; j < m; ++j) {
            for (size_t k = 0; k < m; ++k) {
                if (stdDevs[j] == 0.0 || stdDevs[k] == 0.0) {
                    corrMatrix[j][k] = std::numeric_limits<double>::quiet_NaN();
                } else {
                    corrMatrix[j][k] = covMatrix[j][k] / (stdDevs[j] * stdDevs[k]);
                }
            }
        }

        return corrMatrix;
    }

public:
    DataStatistics2(const std::vector<double>& data) {
        if (data.empty()) {
            data2D = std::vector<std::vector<double>>();
        } else {
            data2D = std::vector<std::vector<double>>(data.size(), std::vector<double>(1));
            for (size_t i = 0; i < data.size(); ++i) {
                data2D[i][0] = data[i];
            }
        }
    }

    double get_sum() {
        std::vector<double> flattened = getFlattenedData();
        if (flattened.empty()) return 0.0;
        return std::accumulate(flattened.begin(), flattened.end(), 0.0);
    }

    double get_min() {
        std::vector<double> flattened = getFlattenedData();
        if (flattened.empty()) return -std::numeric_limits<double>::infinity();
        return *std::min_element(flattened.begin(), flattened.end());
    }

    double get_max() {
        std::vector<double> flattened = getFlattenedData();
        if (flattened.empty()) return std::numeric_limits<double>::infinity();
        return *std::max_element(flattened.begin(), flattened.end());
    }

    double get_variance() {
        std::vector<double> flattened = getFlattenedData();
        if (flattened.empty()) return 0.0;
        double mean = get_sum() / flattened.size();
        double sq_sum = 0.0;
        for (double x : flattened) {
            sq_sum += (x - mean) * (x - mean);
        }
        double variance = sq_sum / flattened.size();
        return std::round(variance * 100.0) / 100.0;
    }

    double get_std_deviation() {
        std::vector<double> flattened = getFlattenedData();
        if (flattened.empty()) return 0.0;
        double variance = get_variance();
        return std::sqrt(variance);
    }

    double get_correlation() {
        auto corrMatrix = computeCorrelationMatrix();
        if (corrMatrix.empty()) {
            return 0.0;
        }
        return corrMatrix[0][0];
    }
};