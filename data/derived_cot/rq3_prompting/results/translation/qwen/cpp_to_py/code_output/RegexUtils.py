import re


class RegexUtils:
    def match(cls, pattern, text):
        return re.search(pattern, text) is not None

    def findall(cls, pattern, text):
        return re.findall(pattern, text)

    def split(cls, pattern, text):
        if text == "":
            return []
        matches = list(re.finditer(pattern, text))
        tokens = []
        start = 0
        for match in matches:
            tokens.append(text[start:match.start()])
            start = match.end()
        tokens.append(text[start:])
        if tokens and tokens[0] != text:
            tokens.append("")
        return tokens

    def sub(cls, pattern, replacement, text):
        return re.sub(pattern, replacement, text)

    @staticmethod
    def generate_email_pattern():
        return r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b'

    @staticmethod
    def generate_phone_number_pattern():
        return r'\b\d{3}-\d{3}-\d{4}\b'

    @staticmethod
    def generate_split_sentences_pattern():
        return r'(?<=[.!?])\s{1,2}(?=[A-Z])'

    def split_sentences(cls, text):
        pattern = cls.generate_split_sentences_pattern()
        sentences = cls.split(pattern, text)
        if sentences and sentences[0] == '':
            sentences.pop(0)
        if sentences and sentences[-1] == '':
            sentences.pop()
        return sentences

    def validate_phone_number(cls, phone_number):
        pattern = cls.generate_phone_number_pattern()
        return cls.match(pattern, phone_number)

    def extract_email(cls, text):
        pattern = cls.generate_email_pattern()
        return cls.findall(pattern, text)