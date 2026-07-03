import re

class SplitSentence:
    def __init__(self):
        self.sentence_pattern = re.compile(r"(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s")
    
    def splitSentences(self, sentencesString):
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

    def countWords(self, sentence):
        cleaned = re.sub(r'[^a-zA-Z\s]', '', sentence)
        if cleaned == "":
            return 1
        words = re.split(r'\s+', cleaned)
        while words and words[-1] == '':
            words.pop()
        return len(words)

    def processTextFile(self, sentencesString):
        sentences = self.splitSentences(sentencesString)
        max_count = 0
        for sentence in sentences:
            count = self.countWords(sentence)
            if count > max_count:
                max_count = count
        return max_count