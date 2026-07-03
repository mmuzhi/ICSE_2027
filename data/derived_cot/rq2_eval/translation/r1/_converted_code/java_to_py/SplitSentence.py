import re

class SplitSentence:

    def __init__(self):
        self.sentence_pattern = re.compile('(?<!\\w\\.\\w.)(?<![A-Z][a-z]\\.)(?<=\\.|\\?)\\s')

    def split_sentences(self, sentencesString):
        sentences = []
        last_end = 0
        for match in self.sentence_pattern.finditer(sentencesString):
            start_index = last_end
            end_index = match.end() - 1
            sentences.append(sentencesString[start_index:end_index])
            last_end = match.end()
        if last_end < len(sentencesString):
            sentences.append(sentencesString[last_end:])
        return sentences

    def count_words(self, sentence):
        cleaned = re.sub('[^a-zA-Z\\s]', '', sentence)
        if cleaned == '':
            return 1
        words = re.split('\\s+', cleaned)
        while words and words[-1] == '':
            words.pop()
        return len(words)

    def process_text_file(self, sentencesString):
        sentences = self.split_sentences(sentencesString)
        max_count = 0
        for sentence in sentences:
            count = self.count_words(sentence)
            if count > max_count:
                max_count = count
        return max_count