#include <vector>
#include <algorithm>

class MetricsCalculator {
public:
    int true_positives = 0;
    int false_positives = 0;
    int false_negatives = 0;
    int true_negatives = 0;

    void update(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        // zip stops at the shortest list
        size_t n = std::min(predicted_labels.size(), true_labels.size());
        for (size_t i = 0; i < n; ++i) {
            int predicted = predicted_labels[i];
            int true_val = true_labels[i];
            if (predicted == 1 && true_val == 1) {
                true_positives += 1;
            } else if (predicted == 1 && true_val == 0) {
                false_positives += 1;
            } else if (predicted == 0 && true_val == 1) {
                false_negatives += 1;
            } else if (predicted == 0 && true_val == 0) {
                true_negatives += 1;
            }
        }
    }

    double precision(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        update(predicted_labels, true_labels);
        if (true_positives + false_positives == 0) {
            return 0.0;
        }
        return static_cast<double>(true_positives) / (true_positives + false_positives);
    }

    double recall(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        update(predicted_labels, true_labels);
        if (true_positives + false_negatives == 0) {
            return 0.0;
        }
        return static_cast<double>(true_positives) / (true_positives + false_negatives);
    }

    double f1_score(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        // Note: The original Python code calls update() here, and then calls 
        // precision() and recall() which also call update(). This means the 
        // internal state gets updated 3 times total per f1_score() call. 
        // We preserve this exact behavior in C++.
        update(predicted_labels, true_labels);
        double prec = precision(predicted_labels, true_labels);
        double rec = recall(predicted_labels, true_labels);
        if (prec + rec == 0.0) {
            return 0.0;
        }
        return (2 * prec * rec) / (prec + rec);
    }

    double accuracy(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        update(predicted_labels, true_labels);
        int total = true_positives + true_negatives + false_positives + false_negatives;
        if (total == 0) {
            return 0.0;
        }
        return static_cast<double>(true_positives + true_negatives) / total;
    }
};