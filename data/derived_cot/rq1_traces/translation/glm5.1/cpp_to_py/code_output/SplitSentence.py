import re


class SplitSentence:
    def split_sentences(self, sentences_string):
        regex = r'(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s'
        parts = re.split(regex, sentences_string)
        sentences = []
        for sentence in parts:
            if sentence:
                # Right-trim whitespace (mirrors the C++ erase + find_if on reverse iterators)
                sentence = sentence.rstrip()
                if sentence:
                    sentences.append(sentence)
        return sentences

    def count_words(self, sentence):
        # Keep only alphabetic and whitespace characters (mirrors remove_copy_if)
        cleaned_sentence = ''.join(
            c for c in sentence
            if c.isalpha() or c.isspace()
        )
        # Count whitespace-separated tokens (mirrors istringstream >> word)
        return len(cleaned_sentence.split())

    def process_text_file(self, sentences_string):
        sentences = self.split_sentences(sentences_string)
        max_count = 0
        for sentence in sentences:
            count = self.count_words(sentence)
            if count > max_count:
                max_count = count
        return max_count