import re

class SplitSentence:
    @staticmethod
    def split_sentences(sentences_string):
        pattern = r"(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?|\!)\s"
        matches = re.finditer(pattern, sentences_string)
        last_end = 0
        sentences = []
        for match in matches:
            start = match.start()
            end = match.end()
            sentences.append(sentences_string[last_end:end-1])
            last_end = end
        if last_end < len(sentences_string):
            sentences.append(sentences_string[last_end:])
        return sentences

    @staticmethod
    def count_words(sentence):
        cleaned_sentence = re.sub(r'[^a-zA-Z\s]', '', sentence)
        words = cleaned_sentence.split()
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