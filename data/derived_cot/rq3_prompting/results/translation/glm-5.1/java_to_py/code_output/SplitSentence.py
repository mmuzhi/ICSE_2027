import re


class SplitSentence:

    def splitSentences(self, sentencesString):
        sentences = []
        pattern = re.compile(r'(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s')
        lastEnd = 0
        for matcher in pattern.finditer(sentencesString):
            sentences.append(sentencesString[lastEnd:matcher.end() - 1])
            lastEnd = matcher.end()
        if lastEnd < len(sentencesString):
            sentences.append(sentencesString[lastEnd:])
        return sentences

    def countWords(self, sentence):
        cleanedSentence = re.sub(r'[^a-zA-Z\s]', '', sentence)
        words = re.split(r'\s+', cleanedSentence)
        # Replicate Java's String.split behavior: remove trailing empty strings
        while words and words[-1] == '':
            words.pop()
        return len(words)

    def processTextFile(self, sentencesString):
        sentences = self.splitSentences(sentencesString)
        maxCount = 0
        for sentence in sentences:
            count = self.countWords(sentence)
            if count > maxCount:
                maxCount = count
        return maxCount