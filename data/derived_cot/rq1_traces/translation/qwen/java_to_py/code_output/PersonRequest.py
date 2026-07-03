class PersonRequest:
    def __init__(self, name, sex, phone_number):
        self.name = self._validate_name(name)
        self.sex = self._validate_sex(sex)
        self.phone_number = self._validate_phone_number(phone_number)

    def _validate_name(self, name):
        if name is None or name == '' or len(name) > 33:
            return None
        return name

    def _validate_sex(self, sex):
        if sex is None or sex not in ('Man', 'Woman', 'UGM'):
            return None
        return sex

    def _validate_phone_number(self, phone_number):
        if phone_number is None or phone_number == '' or len(phone_number) != 11 or not phone_number.isdigit():
            return None
        return phone_number

    def get_name(self):
        return self.name

    def get_sex(self):
        return self.sex

    def get_phone_number(self):
        return self.phone_number