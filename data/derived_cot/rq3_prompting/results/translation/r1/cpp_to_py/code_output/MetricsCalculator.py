class MetricsCalculator:
    def __init__(self):
        self.true_positives = 0
        self.false_positives = 0
        self.false_negatives = 0
        self.true_negatives = 0

    def update(self, predicted_labels, true_labels):
        for pred, true_val in zip(predicted_labels, true_labels):
            if pred == 1 and true_val == 1:
                self.true_positives += 1
            elif pred == 1 and true_val == 0:
                self.false_positives += 1
            elif pred == 0 and true_val == 1:
                self.false_negatives += 1
            elif pred == 0 and true_val == 0:
                self.true_negatives += 1

    def precision(self, predicted_labels, true_labels):
        self.update(predicted_labels, true_labels)
        denom = self.true_positives + self.false_positives
        if denom == 0:
            return 0.0
        return self.true_positives / denom

    def recall(self, predicted_labels, true_labels):
        self.update(predicted_labels, true_labels)
        denom = self.true_positives + self.false_negatives
        if denom == 0:
            return 0.0
        return self.true_positives / denom

    def f1_score(self, predicted_labels, true_labels):
        self.update(predicted_labels, true_labels)
        p = self.precision(predicted_labels, true_labels)
        r = self.recall(predicted_labels, true_labels)
        if p + r == 0.0:
            return 0.0
        return 2.0 * p * r / (p + r)

    def accuracy(self, predicted_labels, true_labels):
        self.update(predicted_labels, true_labels)
        total = self.true_positives + self.true_negatives + self.false_positives + self.false_negatives
        if total == 0:
            return 0.0
        return (self.true_positives + self.true_negatives) / total