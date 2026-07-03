class PersonRequest:
    def __init__(self, name, sex, phoneNumber):
        self.name = self.validate_name(name)
        self.sex = self.validate_sex(sex)
        self.phoneNumber = self.validate_phoneNumber(phoneNumber)
    
    @staticmethod
    def validate_name(name):
        if name is None or len(name) == 0 or len(name) > 33:
            return None
        return name
    
    @staticmethod
    def validate_sex(sex):
        valid_sexes = {"Man", "Woman", "UGM"}
        if sex is None or sex not in valid_sexes:
            return None
        return sex
    
    @staticmethod
    def validate_phoneNumber(phoneNumber):
        if phoneNumber is None or len(phoneNumber) != 11 or not phoneNumber.isdigit():
            return None
        return phoneNumber
    
    def get_name(self):
        return self.name
    
    def get_sex(self):
        return self.sex
    
    def get_phoneNumber(self):
        return self.phoneNumber