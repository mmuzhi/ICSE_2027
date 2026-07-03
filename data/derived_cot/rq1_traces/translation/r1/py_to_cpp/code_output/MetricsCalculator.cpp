#include <vector>

class MetricsCalculator {
private:
    int true_positives;
    int false_positives;
    int false_negatives;
    int true_negatives;

public:
    MetricsCalculator() : true_positives(0), false_positives(0), false_negatives(0), true_negatives(0) {}

    void update(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        for (size_t i = 0; i < predicted_labels.size(); ++i) {
            int pred = predicted_labels[i];
            int true_val = true_labels[i];
            if (pred == 1 && true_val == 1) {
                true_positives += 1;
            } else if (pred == 1 && true_val == 0) {
                false_positives += 1;
            } else if (pred == 0 && true_val == 1) {
                false_negatives += 1;
            } else if (pred == 0 && true_val == 0) {
                true_negatives += 1;
            }
        }
    }

    double precision(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        update(predicted_labels, true_labels);
        int denom = true_positives + false_positives;
        if (denom == 0) {
            return 0.0;
        }
        return static_cast<double>(true_positives) / denom;
    }

    double recall(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        update(predicted_labels, true_labels);
        int denom = true_positives + false_negatives;
        if (denom == 0) {
            return 0.0;
        }
        return static_cast<double>(true_positives) / denom;
    }

    double f1_score(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        update(predicted_labels, true_labels);
        double p = precision(predicted_labels, true_labels);
        double r = recall(predicted_labels, true_labels);
        if (p + r == 0.0) {
            return 0.0;
        }
        return (2 * p * r) / (p + r);
    }

    double accuracy(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        update(predicted_labels, true_labels);
        int total = true_positives + false_positives + false_negatives + true_negatives;
        if (total == 0) {
            return 0.0;
        }
        return static_cast<double>(true_positives + true_negatives) / total;
    }
};