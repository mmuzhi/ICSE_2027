import re

class RegexUtils:

    def match(self, pattern, text):
        return re.fullmatch(pattern, text) is not None

    def findall(self, pattern, text):
        matches = []
        for match in re.finditer(pattern, text):
            matches.append(match.group(0))
        return matches

    def split(self, pattern, text):
        return re.split(pattern, text)

    def sub(self, pattern, replacement, text):
        return re.sub(pattern, replacement, text)

    def generateEmailPattern(self):
        return r"\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b"

    def generatePhoneNumberPattern(self):
        return r"\b\d{3}-\d{3}-\d{4}\b"

    def generateSplitSentencesPattern(self):
        return r"[.!?][\s]{1,2}(?=[A-Z])"

    def splitSentences(self, text):
        pattern = self.generateSplitSentencesPattern()
        return self.split(pattern, text)

    def validatePhoneNumber(self, phoneNumber):
        pattern = self.generatePhoneNumberPattern()
        return self.match(pattern, phoneNumber)

    def extractEmail(self, text):
        pattern = self.generateEmailPattern()
        return self.findall(pattern, text)