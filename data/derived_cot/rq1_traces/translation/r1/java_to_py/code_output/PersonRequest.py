class PersonRequest:
    def __init__(self, name, sex, phone_number):
        self._name = self._validate_name(name)
        self._sex = self._validate_sex(sex)
        self._phone_number = self._validate_phone_number(phone_number)
    
    def _validate_name(self, name):
        if name is None or name == '' or len(name) > 33:
            return None
        return name
    
    def _validate_sex(self, sex):
        if sex is None:
            return None
        if sex not in ['Man', 'Woman', 'UGM']:
            return None
        return sex
    
    def _validate_phone_number(self, phone_number):
        if phone_number is None or phone_number == '':
            return None
        if len(phone_number) != 11:
            return None
        for c in phone_number:
            if c not in '0123456789':
                return None
        return phone_number
    
    def getName(self):
        return self._name
    
    def getSex(self):
        return self._sex
    
    def getPhoneNumber(self):
        return self._phone_number