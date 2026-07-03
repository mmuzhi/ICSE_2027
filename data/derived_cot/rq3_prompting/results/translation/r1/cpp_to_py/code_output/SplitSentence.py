import re


class SplitSentence:
    def split_sentences(self, sentences_string: str):
        # Regex: matches whitespace after '.' or '?' but not after abbreviations like "U.S." or "Mr."
        # Use a raw string to match the behavior of Boost regex.
        pattern = r"(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s"
        parts = re.split(pattern, sentences_string)
        sentences = []
        for s in parts:
            # Trim trailing whitespace (as in C++ std::isspace for trailing chars)
            s = s.rstrip()
            if s:
                sentences.append(s)
        return sentences

    def count_words(self, sentence: str) -> int:
        # Keep only alphabetic characters and whitespace (remove punctuation, digits, etc.)
        cleaned = ''.join(c for c in sentence if c.isalpha() or c.isspace())
        # Split on whitespace and count words
        return len(cleaned.split())

    def process_text_file(self, sentences_string: str) -> int:
        sentences = self.split_sentences(sentences_string)
        max_count = 0
        for sentence in sentences:
            count = self.count_words(sentence)
            if count > max_count:
                max_count = count
        return max_count