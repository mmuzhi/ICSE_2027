#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <stdexcept>

class VectorUtil {
public:
    static double similarity(const std::vector<double>& vector_1, const std::vector<double>& vector_2) {
        auto u1 = unitvec(vector_1);
        auto u2 = unitvec(vector_2);
        return dot(u1, u2);
    }

    static std::vector<double> cosine_similarities(const std::vector<double>& vector_1, const std::vector<std::vector<double>>& vectors_all) {
        double norm1 = norm(vector_1);
        std::vector<double> all_norms(vectors_all.size());
        for (size_t i = 0; i < vectors_all.size(); ++i) {
            all_norms[i] = norm(vectors_all[i]);
        }

        std::vector<double> dot_products(vectors_all.size());
        for (size_t i = 0; i < vectors_all.size(); ++i) {
            dot_products[i] = dot(vector_1, vectors_all[i]);
        }

        std::vector<double> similarities(vectors_all.size());
        for (size_t i = 0; i < vectors_all.size(); ++i) {
            similarities[i] = dot_products[i] / (norm1 * all_norms[i]);
        }
        return similarities;
    }

    static double n_similarity(const std::vector<std::vector<double>>& vector_list_1,
                               const std::vector<std::vector<double>>& vector_list_2) {
        if (vector_list_1.empty() || vector_list_2.empty()) {
            throw std::runtime_error("At least one of the passed list is empty.");
        }
        auto mean1 = mean_vector(vector_list_1);
        auto mean2 = mean_vector(vector_list_2);
        return dot(unitvec(mean1), unitvec(mean2));
    }

    static std::map<std::string, double> compute_idf_weight_dict(int total_num,
                                                                  const std::map<std::string, double>& number_dict) {
        std::map<std::string, double> result;
        for (const auto& pair : number_dict) {
            double count = pair.second;
            double weight = std::log((total_num + 1.0) / (count + 1.0));
            result[pair.first] = weight;
        }
        return result;
    }

private:
    static double dot(const std::vector<double>& v1, const std::vector<double>& v2) {
        double sum = 0.0;
        for (size_t i = 0; i < v1.size(); ++i) {
            sum += v1[i] * v2[i];
        }
        return sum;
    }

    static double norm(const std::vector<double>& v) {
        double sum_sq = 0.0;
        for (double x : v) {
            sum_sq += x * x;
        }
        return std::sqrt(sum_sq);
    }

    static std::vector<double> unitvec(const std::vector<double>& v) {
        double n = norm(v);
        if (n == 0.0) {
            return std::vector<double>(v.size(), 0.0);
        }
        std::vector<double> result(v.size());
        for (size_t i = 0; i < v.size(); ++i) {
            result[i] = v[i] / n;
        }
        return result;
    }

    static std::vector<double> mean_vector(const std::vector<std::vector<double>>& vec_list) {
        if (vec_list.empty()) return {};
        size_t dim = vec_list[0].size();
        std::vector<double> mean(dim, 0.0);
        for (const auto& vec : vec_list) {
            for (size_t i = 0; i < dim; ++i) {
                mean[i] += vec[i];
            }
        }
        double inv_count = 1.0 / vec_list.size();
        for (double& val : mean) {
            val *= inv_count;
        }
        return mean;
    }
};