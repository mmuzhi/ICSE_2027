#include <vector>
#include <map>
#include <cmath>
#include <stdexcept>
#include <utility>

class VectorUtil {

public:
    static double similarity(const std::vector<double>& vector1, const std::vector<double>& vector2) {
        if (vector1.size() != vector2.size()) {
            throw std::invalid_argument("Vectors must be of the same length");
        }

        double dotProduct = 0.0;
        double norm1 = 0.0;
        double norm2 = 0.0;

        for (size_t i = 0; i < vector1.size(); ++i) {
            dotProduct += vector1[i] * vector2[i];
            norm1 += vector1[i] * vector1[i];
            norm2 += vector2[i] * vector2[i];
        }

        double denominator = std::sqrt(norm1) * std::sqrt(norm2);
        return denominator == 0.0 ? 0.0 : dotProduct / denominator;
    }

    static std::vector<double> cosineSimilarities(const std::vector<double>& vector1, const std::vector<std::vector<double>>& vectorsAll) {
        std::vector<double> similarities;

        // Compute norm of vector1
        double norm1 = std::sqrt(dotProduct(vector1, vector1));
        if (norm1 == 0.0) {
            // If vector1 is zero, all similarities are zero
            for (const auto& vec : vectorsAll) {
                similarities.push_back(0.0);
            }
            return similarities;
        }

        for (const auto& vector2 : vectorsAll) {
            // Check if vector2 is valid
            if (vector1.size() != vector2.size()) {
                throw std::invalid_argument("Vectors must be of the same length");
            }

            double norm2 = std::sqrt(dotProduct(vector2, vector2));
            if (norm2 == 0.0) {
                similarities.push_back(0.0);
            } else {
                similarities.push_back(dotProduct(vector1, vector2) / (norm1 * norm2));
            }
        }

        return similarities;
    }

    static double n_similarity(const std::vector<std::vector<double>>& vectorList1, const std::vector<std::vector<double>>& vectorList2) {
        if (vectorList1.empty() || vectorList2.empty()) {
            throw std::invalid_argument("At least one of the passed lists is empty.");
        }

        auto avgVector1 = averageVector(vectorList1);
        auto avgVector2 = averageVector(vectorList2);
        return similarity(avgVector1, avgVector2);
    }

    static std::map<std::string, double> computeIdfWeightDict(int totalNum, const std::map<std::string, double>& numberDict) {
        std::map<std::string, double> result;
        for (const auto& entry : numberDict) {
            double count = entry.second;
            double weight = std::log(static_cast<double>(totalNum + 1) / (count + 1));
            result[entry.first] = weight;
        }
        return result;
    }

private:
    static double dotProduct(const std::vector<double>& vector1, const std::vector<double>& vector2) {
        if (vector1.size() != vector2.size()) {
            throw std::invalid_argument("Vectors must be of the same length");
        }

        double result = 0.0;
        for (size_t i = 0; i < vector1.size(); ++i) {
            result += vector1[i] * vector2[i];
        }
        return result;
    }

    static std::vector<double> averageVector(const std::vector<std::vector<double>>& vectors) {
        if (vectors.empty()) {
            throw std::invalid_argument("Cannot compute average of empty vector list");
        }

        size_t dimension = vectors[0].size();
        std::vector<double> avgVector(dimension, 0.0);

        for (const auto& vec : vectors) {
            if (vec.size() != dimension) {
                throw std::invalid_argument("Vectors in the list must have the same dimension");
            }
            for (size_t i = 0; i < dimension; ++i) {
                avgVector[i] += vec[i];
            }
        }

        double numVectors = vectors.size();
        for (size_t i = 0; i < dimension; ++i) {
            avgVector[i] /= numVectors;
        }

        return avgVector;
    }
};