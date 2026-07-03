import re

class SplitSentence:
    def split_sentences(self, sentences_string):
        pattern = r'(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s'
        parts = re.split(pattern, sentences_string)
        sentences = []
        for part in parts:
            if part:
                # Trim trailing whitespace
                sentence = part.rstrip()
                if sentence:
                    sentences.append(sentence)
        return sentences

    def count_words(self, sentence):
        # Remove all non-alphabetic and non-space characters
        cleaned = ''.join(filter(lambda c: c.isalpha() or c.isspace(), sentence))
        # Split by spaces and count words
        words = cleaned.split()
        return len(words)

    def process_text_file(self, sentences_string):
        sentences = self.split_sentences(sentences_string)
        max_count = 0
        for sentence in sentences:
            count = self.count_words(sentence)
            if count > max_count:
                max_count = count
        return max_count