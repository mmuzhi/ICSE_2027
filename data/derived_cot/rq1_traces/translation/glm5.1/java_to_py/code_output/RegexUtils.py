import re
from typing import List

class RegexUtils:

    def match(self, pattern: str, text: str) -> bool:
        # Java's matches() checks the entire region, equivalent to re.fullmatch in Python
        return re.fullmatch(pattern, text) is not None

    def findall(self, pattern: str, text: str) -> List[str]:
        # Using finditer to consistently return the full match (group 0), 
        # avoiding Python's re.findall behavior which returns tuples if capturing groups are present.
        return [m.group(0) for m in re.finditer(pattern, text)]

    def split(self, pattern: str, text: str) -> List[str]:
        # Python's re.split preserves trailing empty strings by default, 
        # which matches Java's split(text, -1) behavior.
        return re.split(pattern, text)

    def sub(self, pattern: str, replacement: str, text: str) -> str:
        return re.sub(pattern, replacement, text)

    def generate_email_pattern(self) -> str:
        # Using raw strings to preserve regex escapes identically
        return r"\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b"

    def generate_phone_number_pattern(self) -> str:
        return r"\b\d{3}-\d{3}-\d{4}\b"

    def generate_split_sentences_pattern(self) -> str:
        return r"[.!?][\s]{1,2}(?=[A-Z])"

    def split_sentences(self, text: str) -> List[str]:
        pattern = self.generate_split_sentences_pattern()
        return self.split(pattern, text)

    def validate_phone_number(self, phone_number: str) -> bool:
        pattern = self.generate_phone_number_pattern()
        return self.match(pattern, phone_number)

    def extract_email(self, text: str) -> List[str]:
        pattern = self.generate_email_pattern()
        return self.findall(pattern, text)