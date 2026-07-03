class PersonRequest:

    def __init__(self, name, sex, phoneNumber):
        self.name = self._validate_name(name)
        self.sex = self._validate_sex(sex)
        self.phoneNumber = self._validate_phoneNumber(phoneNumber)

    def _validate_name(self, name):
        if name == '' or len(name) > 33:
            return ''
        return name

    def _validate_sex(self, sex):
        if sex not in ['Man', 'Woman', 'UGM']:
            return ''
        return sex

    def _validate_phoneNumber(self, phoneNumber):
        if phoneNumber == '' or len(phoneNumber) != 11 or (not self._is_all_digits(phoneNumber)):
            return ''
        return phoneNumber

    def _is_all_digits(self, s):
        for c in s:
            if c not in '0123456789':
                return False
        return True