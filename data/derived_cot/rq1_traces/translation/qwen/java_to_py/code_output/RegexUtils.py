import re

class RegexUtils:

    def match(pattern, text):
        compiled_pattern = re.compile(pattern)
        return compiled_pattern.fullmatch(text) is not None

    def findall(pattern, text):
        compiled_pattern = re.compile(pattern)
        return list(compiled_pattern.findall(text))

    def split(pattern, text):
        compiled_pattern = re.compile(pattern)
        return compiled_pattern.split(text, maxsplit=-1)

    def sub(pattern, replacement, text):
        compiled_pattern = re.compile(pattern)
        return compiled_pattern.sub(replacement, text)

    def generateEmailPattern():
        return r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b'

    def generatePhoneNumberPattern():
        return r'\b\d{3}-\d{3}-\d{4}\b'

    def generateSplitSentencesPattern():
        return r'[.!?][\s]{1,2}(?=[A-Z])'

    def splitSentences(text):
        pattern = RegexUtils.generateSplitSentencesPattern()
        return RegexUtils.split(pattern, text)

    def validatePhoneNumber(phoneNumber):
        pattern = RegexUtils.generatePhoneNumberPattern()
        return RegexUtils.match(pattern, phoneNumber)

    def extractEmail(text):
        pattern = RegexUtils.generateEmailPattern()
        return RegexUtils.findall(pattern, text)