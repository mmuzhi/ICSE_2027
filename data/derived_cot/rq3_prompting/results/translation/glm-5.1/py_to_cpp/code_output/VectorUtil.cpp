#include <vector>
#include <map>
#include <cmath>
#include <stdexcept>
#include <string>

class VectorUtil {
public:
    static std::vector<double> unitvec(const std::vector<double>& v) {
        double norm = 0.0;
        for (double x : v) norm += x * x;
        norm = std::sqrt(norm);
        std::vector<double> result(v.size());
        for (size_t i = 0; i < v.size(); ++i) {
            result[i] = v[i] / norm;
        }
        return result;
    }

    static double dot(const std::vector<double>& a, const std::vector<double>& b) {
        double result = 0.0;
        for (size_t i = 0; i < a.size(); ++i) {
            result += a[i] * b[i];
        }
        return result;
    }

    static double similarity(const std::vector<double>& vector_1, const std::vector<double>& vector_2) {
        auto u1 = unitvec(vector_1);
        auto u2 = unitvec(vector_2);
        return dot(u1, u2);
    }

    static std::vector<double> cosine_similarities(const std::vector<double>& vector_1,
                                                    const std::vector<std::vector<double>>& vectors_all) {
        double norm = 0.0;
        for (double x : vector_1) norm += x * x;
        norm = std::sqrt(norm);

        std::vector<double> all_norms(vectors_all.size());
        for (size_t i = 0; i < vectors_all.size(); ++i) {
            double n = 0.0;
            for (double x : vectors_all[i]) n += x * x;
            all_norms[i] = std::sqrt(n);
        }

        std::vector<double> similarities(vectors_all.size());
        for (size_t i = 0; i < vectors_all.size(); ++i) {
            double dp = dot(vectors_all[i], vector_1);
            similarities[i] = dp / (norm * all_norms[i]);
        }
        return similarities;
    }

    static double n_similarity(const std::vector<std::vector<double>>& vector_list_1,
                                const std::vector<std::vector<double>>& vector_list_2) {
        if (vector_list_1.empty() || vector_list_2.empty()) {
            throw std::runtime_error("At least one of the passed list is empty.");
        }

        size_t dim1 = vector_list_1[0].size();
        std::vector<double> mean1(dim1, 0.0);
        for (const auto& v : vector_list_1) {
            for (size_t i = 0; i < dim1; ++i) {
                mean1[i] += v[i];
            }
        }
        for (size_t i = 0; i < dim1; ++i) {
            mean1[i] /= static_cast<double>(vector_list_1.size());
        }

        size_t dim2 = vector_list_2[0].size();
        std::vector<double> mean2(dim2, 0.0);
        for (const auto& v : vector_list_2) {
            for (size_t i = 0; i < dim2; ++i) {
                mean2[i] += v[i];
            }
        }
        for (size_t i = 0; i < dim2; ++i) {
            mean2[i] /= static_cast<double>(vector_list_2.size());
        }

        return dot(unitvec(mean1), unitvec(mean2));
    }

    static std::map<std::string, double> compute_idf_weight_dict(int total_num,
                                                                    const std::map<std::string, double>& number_dict) {
        std::map<std::string, double> result;
        for (const auto& kv : number_dict) {
            result[kv.first] = std::log((total_num + 1.0) / (kv.second + 1.0));
        }
        return result;
    }
};