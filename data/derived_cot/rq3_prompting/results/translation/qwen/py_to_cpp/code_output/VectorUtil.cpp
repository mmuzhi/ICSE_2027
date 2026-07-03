#include <vector>
#include <cmath>
#include <unordered_map>
#include <stdexcept>

class VectorUtil {
public:
    static double similarity(const std::vector<double>& vector_1, const std::vector<double>& vector_2) {
        // Calculate norms
        double norm1 = 0.0, norm2 = 0.0;
        for (double x : vector_1) norm1 += x * x;
        for (double x : vector_2) norm2 += x * x;
        norm1 = std::sqrt(norm1);
        norm2 = std::sqrt(norm2);

        // Calculate dot product
        double dot_product = 0.0;
        for (size_t i = 0; i < vector_1.size(); ++i) {
            dot_product += vector_1[i] * vector_2[i];
        }

        return dot_product / (norm1 * norm2);
    }

    static std::vector<double> cosine_similarities(const std::vector<double>& vector_1, const std::vector<std::vector<double>>& vectors_all) {
        if (vector_1.empty() || vectors_all.empty()) {
            throw std::invalid_argument("Both vector_1 and vectors_all must be non-empty");
        }

        size_t dim = vector_1.size();
        std::vector<double> similarities;

        // Calculate norm for vector_1
        double norm1 = 0.0;
        for (double x : vector_1) norm1 += x * x;
        norm1 = std::sqrt(norm1);

        for (const auto& vec : vectors_all) {
            if (vec.empty() || vec.size() != dim) {
                throw std::invalid_argument("All vectors in vectors_all must have the same dimension as vector_1");
            }

            // Calculate norm for current vector
            double norm2 = 0.0;
            for (double x : vec) norm2 += x * x;
            norm2 = std::sqrt(norm2);

            // Calculate dot product
            double dot_product = 0.0;
            for (size_t i = 0; i < dim; ++i) {
                dot_product += vector_1[i] * vec[i];
            }

            similarities.push_back(dot_product / (norm1 * norm2));
        }

        return similarities;
    }

    static double n_similarity(const std::vector<std::vector<double>>& vector_list_1, const std::vector<std::vector<double>>& vector_list_2) {
        if (vector_list_1.empty() || vector_list_2.empty()) {
            throw std::invalid_argument("Both vector_list_1 and vector_list_2 must be non-empty");
        }

        // Calculate mean vector for vector_list_1
        std::vector<double> mean1;
        if (vector_list_1.empty()) {
            throw std::invalid_argument("vector_list_1 is empty");
        }
        size_t dim = vector_list_1[0].size();
        mean1.resize(dim, 0.0);
        for (const auto& vec : vector_list_1) {
            for (size_t i = 0; i < dim; ++i) {
                mean1[i] += vec[i];
            }
        }
        for (double& x : mean1) x /= vector_list_1.size();

        // Calculate mean vector for vector_list_2
        std::vector<double> mean2;
        if (vector_list_2.empty()) {
            throw std::invalid_argument("vector_list_2 is empty");
        }
        mean2.resize(dim, 0.0);
        for (const auto& vec : vector_list_2) {
            for (size_t i = 0; i < dim; ++i) {
                mean2[i] += vec[i];
            }
        }
        for (double& x : mean2) x /= vector_list_2.size();

        return VectorUtil::similarity(mean1, mean2);
    }

    static std::unordered_map<std::string, double> compute_idf_weight_dict(int total_num, const std::unordered_map<std::string, double>& number_dict) {
        std::vector<std::pair<std::string, double>> temp;
        for (const auto& kv : number_dict) {
            temp.push_back(kv);
        }

        std::unordered_map<std::string, double> result;
        for (const auto& kv : temp) {
            double count = kv.second;
            double value = std::log(static_cast<double>(total_num + 1) / (count + 1));
            result[kv.first] = value;
        }

        return result;
    }
};