#include <vector>
#include <cmath>
#include <stdexcept>
#include <map>
#include <string>

namespace VectorUtil {

    double dot_product(const std::vector<double>& a, const std::vector<double>& b) {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Vectors must be of the same size");
        }
        double result = 0.0;
        for (size_t i = 0; i < a.size(); ++i) {
            result += a[i] * b[i];
        }
        return result;
    }

    std::vector<double> normalize(const std::vector<double>& v) {
        double norm = 0.0;
        for (double x : v) {
            norm += x * x;
        }
        norm = std::sqrt(norm);
        if (norm == 0) {
            return v;
        }
        std::vector<double> result;
        result.reserve(v.size());
        for (double x : v) {
            result.push_back(x / norm);
        }
        return result;
    }

    std::vector<double> mean(const std::vector<std::vector<double>>& vecs) {
        if (vecs.empty()) {
            throw std::runtime_error("Cannot compute mean of empty vector");
        }
        size_t n = vecs[0].size();
        for (const auto& vec : vecs) {
            if (vec.size() != n) {
                throw std::invalid_argument("All vectors must have the same size");
            }
        }
        std::vector<double> result(n, 0.0);
        for (const auto& vec : vecs) {
            for (size_t i = 0; i < n; ++i) {
                result[i] += vec[i];
            }
        }
        for (size_t i = 0; i < n; ++i) {
            result[i] /= vecs.size();
        }
        return result;
    }

    static double similarity(const std::vector<double>& vector_1, const std::vector<double>& vector_2) {
        auto unit_vec1 = normalize(vector_1);
        auto unit_vec2 = normalize(vector_2);
        return dot_product(unit_vec1, unit_vec2);
    }

    static std::vector<double> cosine_similarities(const std::vector<double>& vector_1, const std::vector<std::vector<double>>& vectors_all) {
        if (vector_1.empty()) {
            throw std::invalid_argument("vector_1 must not be empty");
        }
        if (!vectors_all.empty() && vectors_all[0].size() != vector_1.size()) {
            throw std::invalid_argument("All vectors in vectors_all must have the same size as vector_1");
        }

        double norm = 0.0;
        for (double x : vector_1) {
            norm += x * x;
        }
        norm = std::sqrt(norm);
        if (norm == 0) {
            throw std::runtime_error("vector_1 is a zero vector");
        }

        std::vector<double> all_norms;
        for (const auto& vec : vectors_all) {
            double norm_i = 0.0;
            for (double x : vec) {
                norm_i += x * x;
            }
            norm_i = std::sqrt(norm_i);
            if (norm_i == 0) {
                throw std::runtime_error("A vector in vectors_all is a zero vector");
            }
            all_norms.push_back(norm_i);
        }

        std::vector<double> dot_products;
        for (const auto& vec : vectors_all) {
            double dp = 0.0;
            for (size_t i = 0; i < vec.size(); ++i) {
                dp += vector_1[i] * vec[i];
            }
            dot_products.push_back(dp);
        }

        std::vector<double> similarities;
        for (size_t i = 0; i < vectors_all.size(); ++i) {
            similarities.push_back(dot_products[i] / (norm * all_norms[i]));
        }

        return similarities;
    }

    static double n_similarity(const std::vector<std::vector<double>>& vector_list_1, const std::vector<std::vector<double>>& vector_list_2) {
        if (vector_list_1.empty() || vector_list_2.empty()) {
            throw std::runtime_error("At least one of the passed list is empty");
        }

        auto mean1 = mean(vector_list_1);
        auto mean2 = mean(vector_list_2);
        auto unit_mean1 = normalize(mean1);
        auto unit_mean2 = normalize(mean2);
        return dot_product(unit_mean1, unit_mean2);
    }

    static std::map<std::string, double> compute_idf_weight_dict(int total_num, const std::map<std::string, double>& number_dict) {
        std::map<std::string, double> result;
        for (const auto& kv : number_dict) {
            double count = kv.second;
            double idf = std::log(static_cast<double>(total_num + 1) / (count + 1));
            result[kv.first] = idf;
        }
        return result;
    }

}

class VectorUtil {
public:
    static double similarity(const std::vector<double>& vector_1, const std::vector<double>& vector_2) {
        return VectorUtil::similarity(vector_1, vector_2);
    }

    static std::vector<double> cosine_similarities(const std::vector<double>& vector_1, const std::vector<std::vector<double>>& vectors_all) {
        return VectorUtil::cosine_similarities(vector_1, vectors_all);
    }

    static double n_similarity(const std::vector<std::vector<double>>& vector_list_1, const std::vector<std::vector<double>>& vector_list_2) {
        return VectorUtil::n_similarity(vector_list_1, vector_list_2);
    }

    static std::map<std::string, double> compute_idf_weight_dict(int total_num, const std::map<std::string, double>& number_dict) {
        return VectorUtil::compute_idf_weight_dict(total_num, number_dict);
    }
};