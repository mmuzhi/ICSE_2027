import re


class RegexUtils:

    @staticmethod
    def match(pattern, text):
        return re.fullmatch(pattern, text) is not None

    @staticmethod
    def findall(pattern, text):
        return re.findall(pattern, text)

    @staticmethod
    def split(pattern, text):
        compiled_pattern = re.compile(pattern)
        tokens = []
        start = 0
        matches = compiled_pattern.finditer(text)
        for match in matches:
            tokens.append(text[start:match.start()])
            start = match.end()
        tokens.append(text[start:])
        return tokens

    @staticmethod
    def sub(pattern, replacement, text):
        return re.sub(pattern, replacement, text)

    @staticmethod
    def generateEmailPattern():
        return r"\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b"

    @staticmethod
    def generatePhoneNumberPattern():
        return r"\b\d{3}-\d{3}-\d{4}\b"

    @staticmethod
    def generateSplitSentencesPattern():
        return r"[.!?][\s]{1,2}(?=[A-Z])"

    @staticmethod
    def splitSentences(text):
        pattern = RegexUtils.generateSplitSentencesPattern()
        return RegexUtils.split(pattern, text)

    @staticmethod
    def validatePhoneNumber(phoneNumber):
        pattern = RegexUtils.generatePhoneNumberPattern()
        return RegexUtils.match(pattern, phoneNumber)

    @staticmethod
    def extractEmail(text):
        pattern = RegexUtils.generateEmailPattern()
        return RegexUtils.findall(pattern, text)