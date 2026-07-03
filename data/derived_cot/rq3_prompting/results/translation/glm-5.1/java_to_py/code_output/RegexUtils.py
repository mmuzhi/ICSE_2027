import re
from typing import List


class RegexUtils:

    def match(self, pattern: str, text: str) -> bool:
        compiled_pattern = re.compile(pattern)
        return compiled_pattern.fullmatch(text) is not None

    def findall(self, pattern: str, text: str) -> List[str]:
        compiled_pattern = re.compile(pattern)
        return compiled_pattern.findall(text)

    def split(self, pattern: str, text: str) -> List[str]:
        compiled_pattern = re.compile(pattern)
        return compiled_pattern.split(text)

    def sub(self, pattern: str, replacement: str, text: str) -> str:
        compiled_pattern = re.compile(pattern)
        return compiled_pattern.sub(replacement, text)

    def generateEmailPattern(self) -> str:
        return r"\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b"

    def generatePhoneNumberPattern(self) -> str:
        return r"\b\d{3}-\d{3}-\d{4}\b"

    def generateSplitSentencesPattern(self) -> str:
        return r"[.!?][\s]{1,2}(?=[A-Z])"

    def splitSentences(self, text: str) -> List[str]:
        pattern = self.generateSplitSentencesPattern()
        return self.split(pattern, text)

    def validatePhoneNumber(self, phone_number: str) -> bool:
        pattern = self.generatePhoneNumberPattern()
        return self.match(pattern, phone_number)

    def extractEmail(self, text: str) -> List[str]:
        pattern = self.generateEmailPattern()
        return self.findall(pattern, text)