import re


class SplitSentence:
    @staticmethod
    def split_sentences(sentences_string):
        pattern = r'(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s'
        tokens = re.split(pattern, sentences_string)
        sentences = []
        for token in tokens:
            if token:
                token = token.rstrip()
                if token:
                    sentences.append(token)
        return sentences

    @staticmethod
    def count_words(sentence):
        if not sentence:
            return 0
        cleaned = re.sub(r'[^a-zA-Z\s]', '', sentence)
        words = cleaned.split()
        return len(words)

    @staticmethod
    def process_text_file(sentences_string):
        sentences = SplitSentence.split_sentences(sentences_string)
        max_count = 0
        for sentence in sentences:
            count = SplitSentence.count_words(sentence)
            if count > max_count:
                max_count = count
        return max_count