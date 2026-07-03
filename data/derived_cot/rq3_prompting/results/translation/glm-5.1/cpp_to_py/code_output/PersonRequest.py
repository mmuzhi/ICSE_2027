class PersonRequest:
    def __init__(self, name: str, sex: str, phone_number: str):
        self.name = self._validate_name(name)
        self.sex = self._validate_sex(sex)
        self.phoneNumber = self._validate_phone_number(phone_number)

    @staticmethod
    def _validate_name(name: str) -> str:
        if not name or len(name) > 33:
            return ""
        return name

    @staticmethod
    def _validate_sex(sex: str) -> str:
        if sex not in ("Man", "Woman", "UGM"):
            return ""
        return sex

    @staticmethod
    def _validate_phone_number(phone_number: str) -> str:
        if not phone_number or len(phone_number) != 11 or not phone_number.isdecimal():
            return ""
        return phone_number