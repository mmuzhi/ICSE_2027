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
            int predicted = predicted_labels[i];
            int true_label = true_labels[i];
            if (predicted == 1 && true_label == 1) {
                true_positives++;
            } else if (predicted == 1 && true_label == 0) {
                false_positives++;
            } else if (predicted == 0 && true_label == 1) {
                false_negatives++;
            } else if (predicted == 0 && true_label == 0) {
                true_negatives++;
            }
        }
    }

    double precision(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        update(predicted_labels, true_labels);
        if (true_positives + false_positives == 0) return 0.0;
        return static_cast<double>(true_positives) / (true_positives + false_positives);
    }

    double recall(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        update(predicted_labels, true_labels);
        if (true_positives + false_negatives == 0) return 0.0;
        return static_cast<double>(true_positives) / (true_positives + false_negatives);
    }

    double f1_score(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        update(predicted_labels, true_labels);
        double precision_val = precision(predicted_labels, true_labels);
        double recall_val = recall(predicted_labels, true_labels);
        if (precision_val + recall_val == 0.0) return 0.0;
        return (2 * precision_val * recall_val) / (precision_val + recall_val);
    }

    double accuracy(const std::vector<int>& predicted_labels, const std::vector<int>& true_labels) {
        update(predicted_labels, true_labels);
        int total = true_positives + true_negatives + false_positives + false_negatives;
        if (total == 0) return 0.0;
        return static_cast<double>(true_positives + true_negatives) / total;
    }
};