class MetricsCalculator:
    def __init__(self):
        self.true_positives = 0
        self.false_positives = 0
        self.false_negatives = 0
        self.true_negatives = 0

    def update(self, predicted_labels, true_labels):
        for predicted, true_label in zip(predicted_labels, true_labels):
            if predicted == 1 and true_label == 1:
                self.true_positives += 1
            elif predicted == 1 and true_label == 0:
                self.false_positives += 1
            elif predicted == 0 and true_label == 1:
                self.false_negatives += 1
            elif predicted == 0 and true_label == 0:
                self.true_negatives += 1

    def precision(self, predicted_labels, true_labels):
        self.update(predicted_labels, true_labels)
        total = self.true_positives + self.false_positives
        return 0.0 if total == 0 else self.true_positives / total

    def recall(self, predicted_labels, true_labels):
        self.update(predicted_labels, true_labels)
        total = self.true_positives + self.false_negatives
        return 0.0 if total == 0 else self.true_positives / total

    def f1_score(self, predicted_labels, true_labels):
        self.update(predicted_labels, true_labels)
        precision_val = self.precision(predicted_labels, true_labels)
        recall_val = self.recall(predicted_labels, true_labels)
        if precision_val + recall_val == 0:
            return 0.0
        return 2 * precision_val * recall_val / (precision_val + recall_val)

    def accuracy(self, predicted_labels, true_labels):
        self.update(predicted_labels, true_labels)
        total = self.true_positives + self.true_negatives + self.false_positives + self.false_negatives
        return 0.0 if total == 0 else (self.true_positives + self.true_negatives) / total