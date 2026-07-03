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

    def generate_email_pattern():
        return '\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b'

    def generate_phone_number_pattern():
        return '\\b\\d{3}-\\d{3}-\\d{4}\\b'

    def generate_split_sentences_pattern():
        return '[.!?][\\s]{1,2}(?=[A-Z])'

    def split_sentences(text):
        pattern = RegexUtils.generateSplitSentencesPattern()
        return RegexUtils.split(pattern, text)

    def validate_phone_number(phoneNumber):
        pattern = RegexUtils.generatePhoneNumberPattern()
        return RegexUtils.match(pattern, phoneNumber)

    def extract_email(text):
        pattern = RegexUtils.generateEmailPattern()
        return RegexUtils.findall(pattern, text)