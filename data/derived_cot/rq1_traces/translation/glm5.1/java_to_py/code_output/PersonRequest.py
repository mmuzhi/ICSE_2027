import re
from typing import Optional

class PersonRequest:
    def __init__(self, name: Optional[str], sex: Optional[str], phone_number: Optional[str]):
        self.name = self._validate_name(name)
        self.sex = self._validate_sex(sex)
        self.phone_number = self._validate_phone_number(phone_number)

    @staticmethod
    def _validate_name(name: Optional[str]) -> Optional[str]:
        # In Java, `name == null || name.isEmpty()` is equivalent to `not name` in Python.
        # `not name` short-circuits if name is None, preventing TypeError on len().
        if not name or len(name) > 33:
            return None
        return name

    @staticmethod
    def _validate_sex(sex: Optional[str]) -> Optional[str]:
        if sex is None or sex not in ("Man", "Woman", "UGM"):
            return None
        return sex

    @staticmethod
    def _validate_phone_number(phone_number: Optional[str]) -> Optional[str]:
        # `not phone_number` handles `null` and `isEmpty()` safely with short-circuiting.
        # `re.fullmatch(r'[0-9]{11}', ...)` is used over `\d` to strictly match Java's 
        # default ASCII-only digit matching behavior of `String.matches("\\d{11}")`.
        if not phone_number or len(phone_number) != 11 or not re.fullmatch(r'[0-9]{11}', phone_number):
            return None
        return phone_number

    def getName(self) -> Optional[str]:
        return self.name

    def getSex(self) -> Optional[str]:
        return self.sex

    def getPhoneNumber(self) -> Optional[str]:
        return self.phone_number