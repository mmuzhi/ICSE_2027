class FitnessTracker:
    BMI_std = {
        "male": [20.0, 25.0],
        "female": [19.0, 24.0]
    }

    def __init__(self, height: float, weight: float, age: int, sex: str):
        self.height = height
        self.weight = weight
        self.age = age
        self.sex = sex

    def get_BMI(self) -> float:
        return self.weight / (self.height * self.height)

    def condition_judge(self) -> int:
        bmi = self.get_BMI()
        # Equivalent to C++'s std::unordered_map::at(), raises KeyError if sex is not found
        bmi_range = FitnessTracker.BMI_std[self.sex]
        
        if bmi > bmi_range[1]:
            return 1
        elif bmi < bmi_range[0]:
            return -1
        else:
            return 0

    def calculate_calorie_intake(self) -> float:
        if self.sex == "male":
            bmr = 10 * self.weight + 6.25 * self.height - 5 * self.age + 5
        else:
            bmr = 10 * self.weight + 6.25 * self.height - 5 * self.age - 161

        condition = self.condition_judge()
        
        if condition == 1:
            calorie_intake = bmr * 1.2
        elif condition == -1:
            calorie_intake = bmr * 1.6
        else:
            calorie_intake = bmr * 1.4
            
        return calorie_intake