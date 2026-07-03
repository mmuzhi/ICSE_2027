import re

class PersonRequest:
    def __init__(self, name: str, sex: str, phoneNumber: str):
        self._name = self._validate_name(name)
        self._sex = self._validate_sex(sex)
        self._phoneNumber = self._validate_phone_number(phoneNumber)

    def _validate_name(self, name: str) -> str:
        if name is None or name == "" or len(name) > 33:
            return None
        return name

    def _validate_sex(self, sex: str) -> str:
        if sex is None or sex not in ("Man", "Woman", "UGM"):
            return None
        return sex

    def _validate_phone_number(self, phoneNumber: str) -> str:
        if phoneNumber is None or len(phoneNumber) != 11 or not phoneNumber.isdigit():
            return None
        return phoneNumber

    def getName(self) -> str:
        return self._name

    def getSex(self) -> str:
        return self._sex

    def getPhoneNumber(self) -> str:
        return self._phoneNumber