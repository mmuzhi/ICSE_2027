class FitnessTracker:

    def __init__(self, height, weight, age, sex):
        self.height = height
        self.weight = weight
        self.age = age
        self.sex = sex
        self.BMI_std = [[20.0, 25.0], [19.0, 24.0]]

    def get_BMI(self):
        return self.weight / (self.height * self.height)

    def condition_judge(self):
        BMI = self.get_BMI()
        index = 0 if self.sex == 'male' else 1
        if BMI > self.BMI_std[index][1]:
            return 1
        elif BMI < self.BMI_std[index][0]:
            return -1
        else:
            return 0

    def calculate_calorie_intake(self):
        if self.sex == 'male':
            BMR = 10 * self.weight + 6.25 * self.height - 5 * self.age + 5
        else:
            BMR = 10 * self.weight + 6.25 * self.height - 5 * self.age - 161
        condition = self.condition_judge()
        if condition == 1:
            return BMR * 1.2
        elif condition == -1:
            return BMR * 1.6
        else:
            return BMR * 1.4