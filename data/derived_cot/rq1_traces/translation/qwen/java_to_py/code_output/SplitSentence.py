import re

class SplitSentence:

    def split_sentences(self, sentences_string):
        pattern = re.compile(r'(?<!\w\.\w\.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s')
        matches = pattern.finditer(sentences_string)
        sentences = []
        last_end = 0
        for match in matches:
            sentences.append(sentences_string[last_end:match.start()])
            last_end = match.end()
        if last_end < len(sentences_string):
            sentences.append(sentences_string[last_end:])
        return sentences

    def count_words(self, sentence):
        cleaned_sentence = re.sub(r'[^a-zA-Z\s]', '', sentence)
        words = cleaned_sentence.split()
        return len(words)

    def process_text_file(self, sentences_string):
        sentences = self.split_sentences(sentences_string)
        max_count = 0
        for sentence in sentences:
            count = self.count_words(sentence)
            if count > max_count:
                max_count = count
        return max_count