#include <Eigen/Dense>
#include <vector>
#include <map>
#include <cmath>
#include <stdexcept>
#include <string>

using namespace Eigen;

class VectorUtil {
public:
    static double similarity(const VectorXd& vector_1, const VectorXd& vector_2) {
        VectorXd u1 = unitvec(vector_1);
        VectorXd u2 = unitvec(vector_2);
        return u1.dot(u2);
    }

    static VectorXd cosine_similarities(const VectorXd& vector_1, const std::vector<VectorXd>& vectors_all) {
        size_t n = vectors_all.size();
        if (n == 0) {
            return VectorXd();
        }
        Index d = vector_1.size();

        MatrixXd M(n, d);
        for (size_t i = 0; i < n; ++i) {
            if (vectors_all[i].size() != d) {
                throw std::invalid_argument("All vectors in vectors_all must have the same dimension as vector_1.");
            }
            M.row(i) = vectors_all[i];
        }

        double norm1 = vector_1.norm();
        VectorXd all_norms = M.rowwise().norm();
        VectorXd dot_products = M * vector_1;

        VectorXd result = dot_products.array() / (norm1 * all_norms.array());

        return result;
    }

    static double n_similarity(const std::vector<VectorXd>& vector_list_1, const std::vector<VectorXd>& vector_list_2) {
        if (vector_list_1.empty() || vector_list_2.empty()) {
            throw std::invalid_argument("At least one of the passed list is empty.");
        }

        Index d1 = vector_list_1[0].size();
        for (const auto& v : vector_list_1) {
            if (v.size() != d1) {
                throw std::invalid_argument("Vectors in vector_list_1 must have the same dimension.");
            }
        }
        Index d2 = vector_list_2[0].size();
        for (const auto& v : vector_list_2) {
            if (v.size() != d2) {
                throw std::invalid_argument("Vectors in vector_list_2 must have the same dimension.");
            }
        }
        if (d1 != d2) {
            throw std::invalid_argument("The two sets of vectors must have the same dimension.");
        }

        VectorXd mean1 = VectorXd::Zero(d1);
        for (const auto& v : vector_list_1) {
            mean1 += v;
        }
        mean1 /= vector_list_1.size();

        VectorXd mean2 = VectorXd::Zero(d2);
        for (const auto& v : vector_list_2) {
            mean2 += v;
        }
        mean2 /= vector_list_2.size();

        return similarity(mean1, mean2);
    }

    static std::map<std::string, double> compute_idf_weight_dict(int total_num, const std::map<std::string, double>& number_dict) {
        std::map<std::string, double> result;
        for (const auto& kv : number_dict) {
            result[kv.first] = std::log((total_num + 1) / (kv.second + 1));
        }
        return result;
    }

private:
    static VectorXd unitvec(const VectorXd& vec) {
        double norm_val = vec.norm();
        if (norm_val == 0.0) {
            norm_val = 1.0;
        }
        return vec / norm_val;
    }
};