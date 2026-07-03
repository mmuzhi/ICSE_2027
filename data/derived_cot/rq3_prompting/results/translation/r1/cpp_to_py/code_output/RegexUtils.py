import re

class RegexUtils:
    def match(self, pattern: str, text: str) -> bool:
        return bool(re.search(pattern, text))

    def findall(self, pattern: str, text: str) -> list:
        return re.findall(pattern, text)

    def split(self, pattern: str, text: str) -> list:
        if not text:
            return []
        result = re.split(pattern, text)
        # If any split occurred (first element differs from original text),
        # add a trailing empty string to match C++ behavior.
        if result and result[0] != text:
            result.append("")
        return result

    def sub(self, pattern: str, replacement: str, text: str) -> str:
        return re.sub(pattern, replacement, text)

    def generate_email_pattern(self) -> str:
        return r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b'

    def generate_phone_number_pattern(self) -> str:
        return r'\b\d{3}-\d{3}-\d{4}\b'

    def generate_split_sentences_pattern(self) -> str:
        return r'[.!?][\s]{1,2}(?=[A-Z])'

    def split_sentences(self, text: str) -> list:
        pattern = self.generate_split_sentences_pattern()
        sentences = self.split(pattern, text)
        # Remove at most one leading empty string
        if sentences and sentences[0] == '':
            sentences.pop(0)
        # Remove at most one trailing empty string
        if sentences and sentences[-1] == '':
            sentences.pop()
        return sentences

    def validate_phone_number(self, phone_number: str) -> bool:
        pattern = self.generate_phone_number_pattern()
        return self.match(pattern, phone_number)

    def extract_email(self, text: str) -> list:
        pattern = self.generate_email_pattern()
        return self.findall(pattern, text)