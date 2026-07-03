class FitnessTracker:
    def __init__(self, height, weight, age, sex):
        self.height = float(height)
        self.weight = float(weight)
        self.age = int(age)
        self.sex = str(sex).lower()  # Convert to lowercase for case-insensitive comparison
        self.BMI_std = [[20.0, 25.0], [19.0, 24.0]]  # BMI standards for male and female

    def get_bmi(self):
        return self.weight / (self.height ** 2)

    def condition_judge(self):
        try:
            bmi = self.get_bmi()
            index = 0 if self.sex == "male" else 1
            upper, lower = self.BMI_std[index]
            if bmi > upper:
                return 1
            elif bmi < lower:
                return -1
            else:
                return 0
        except TypeError:
            # Handle potential type errors if inputs are not numbers
            raise ValueError("Invalid input types. Height, weight, age must be numbers, and sex must be a string.")

    def calculate_calorie_intake(self):
        try:
            bmr = 10 * self.weight + 6.25 * self.height - 5 * self.age + (5 if self.sex == "male" else -161)
            condition = self.condition_judge()
            if condition == 1:
                return bmr * 1.2
            elif condition == -1:
                return bmr * 1.6
            else:
                return bmr * 1.4
        except TypeError:
            # Re-raise exception if inputs are invalid
            raise ValueError("Invalid input types. Height, weight, age must be numbers, and sex must be a string.")