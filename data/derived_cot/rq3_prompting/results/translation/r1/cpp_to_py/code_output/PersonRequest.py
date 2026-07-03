class PersonRequest:
    def __init__(self, name: str, sex: str, phone_number: str):
        self.name = self._validate_name(name)
        self.sex = self._validate_sex(sex)
        self.phone_number = self._validate_phone_number(phone_number)

    def _validate_name(self, name: str) -> str:
        if not name or len(name) > 33:
            return ""
        return name

    def _validate_sex(self, sex: str) -> str:
        if sex not in ("Man", "Woman", "UGM"):
            return ""
        return sex

    def _validate_phone_number(self, phone_number: str) -> str:
        if not phone_number or len(phone_number) != 11 or not self._is_all_digits(phone_number):
            return ""
        return phone_number

    def _is_all_digits(self, s: str) -> bool:
        for c in s:
            if c < '0' or c > '9':
                return False
        return True