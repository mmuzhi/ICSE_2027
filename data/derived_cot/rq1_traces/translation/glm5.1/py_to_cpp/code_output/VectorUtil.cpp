#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <stdexcept>
#include <cstddef>

class VectorUtil {
public:
    static double similarity(const std::vector<double>& vector_1, const std::vector<double>& vector_2) {
        std::vector<double> unit_1 = unitvec(vector_1);
        std::vector<double> unit_2 = unitvec(vector_2);
        return dot(unit_1, unit_2);
    }

    static std::vector<double> cosine_similarities(const std::vector<double>& vector_1,
                                                    const std::vector<std::vector<double>>& vectors_all) {
        double norm = vec_norm(vector_1);
        std::vector<double> similarities;
        similarities.reserve(vectors_all.size());
        for (const auto& v : vectors_all) {
            double v_norm = vec_norm(v);
            double dp = dot(v, vector_1);
            similarities.push_back(dp / (norm * v_norm));
        }
        return similarities;
    }

    static double n_similarity(const std::vector<std::vector<double>>& vector_list_1,
                               const std::vector<std::vector<double>>& vector_list_2) {
        if (vector_list_1.empty() || vector_list_2.empty()) {
            throw std::runtime_error("At least one of the passed list is empty.");
        }

        std::vector<double> mean_1 = vec_mean(vector_list_1);
        std::vector<double> mean_2 = vec_mean(vector_list_2);

        return dot(unitvec(mean_1), unitvec(mean_2));
    }

    static std::map<std::string, double> compute_idf_weight_dict(int total_num,
                                                                   const std::map<std::string, double>& number_dict) {
        std::map<std::string, double> result;
        for (const auto& kv : number_dict) {
            result[kv.first] = std::log((static_cast<double>(total_num) + 1.0) / (kv.second + 1.0));
        }
        return result;
    }

private:
    static std::vector<double> unitvec(const std::vector<double>& vec) {
        double norm = vec_norm(vec);
        std::vector<double> result(vec.size());
        for (size_t i = 0; i < vec.size(); ++i) {
            result[i] = vec[i] / norm;
        }
        return result;
    }

    static double dot(const std::vector<double>& a, const std::vector<double>& b) {
        double sum = 0.0;
        for (size_t i = 0; i < a.size(); ++i) {
            sum += a[i] * b[i];
        }
        return sum;
    }

    static double vec_norm(const std::vector<double>& vec) {
        double sum = 0.0;
        for (double v : vec) {
            sum += v * v;
        }
        return std::sqrt(sum);
    }

    static std::vector<double> vec_mean(const std::vector<std::vector<double>>& vecs) {
        size_t dim = vecs[0].size();
        std::vector<double> mean(dim, 0.0);
        for (const auto& v : vecs) {
            for (size_t i = 0; i < dim; ++i) {
                mean[i] += v[i];
            }
        }
        for (size_t i = 0; i < dim; ++i) {
            mean[i] /= static_cast<double>(vecs.size());
        }
        return mean;
    }
};