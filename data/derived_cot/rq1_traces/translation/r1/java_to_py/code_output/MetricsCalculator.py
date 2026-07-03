class MetricsCalculator:
    def __init__(self):
        self.truePositives = 0
        self.falsePositives = 0
        self.falseNegatives = 0
        self.trueNegatives = 0

    def update(self, predictedLabels, trueLabels):
        for i in range(len(predictedLabels)):
            p = predictedLabels[i]
            t = trueLabels[i]
            if p == 1 and t == 1:
                self.truePositives += 1
            elif p == 1 and t == 0:
                self.falsePositives += 1
            elif p == 0 and t == 1:
                self.falseNegatives += 1
            elif p == 0 and t == 0:
                self.trueNegatives += 1

    def precision(self, predictedLabels, trueLabels):
        self.update(predictedLabels, trueLabels)
        denominator = self.truePositives + self.falsePositives
        if denominator == 0:
            return 0.0
        return self.truePositives / denominator

    def recall(self, predictedLabels, trueLabels):
        self.update(predictedLabels, trueLabels)
        denominator = self.truePositives + self.falseNegatives
        if denominator == 0:
            return 0.0
        return self.truePositives / denominator

    def f1Score(self, predictedLabels, trueLabels):
        self.update(predictedLabels, trueLabels)
        p_val = self.precision(predictedLabels, trueLabels)
        r_val = self.recall(predictedLabels, trueLabels)
        if p_val + r_val == 0.0:
            return 0.0
        return (2 * p_val * r_val) / (p_val + r_val)

    def accuracy(self, predictedLabels, trueLabels):
        self.update(predictedLabels, trueLabels)
        total = self.truePositives + self.falsePositives + self.falseNegatives + self.trueNegatives
        if total == 0:
            return 0.0
        correct = self.truePositives + self.trueNegatives
        return correct / total

if __name__ == "__main__":
    mc = MetricsCalculator()
    predictedLabels = [1, 1, 0, 0]
    trueLabels = [1, 0, 0, 1]
    print(mc.precision(predictedLabels, trueLabels))
    print(mc.recall(predictedLabels, trueLabels))
    print(mc.f1Score(predictedLabels, trueLabels))
    print(mc.accuracy(predictedLabels, trueLabels))