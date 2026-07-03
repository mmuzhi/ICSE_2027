import re

class SplitSentence:
    def splitSentences(self, sentencesString):
        sentences = []
        pattern = re.compile(r"(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s")
        lastEnd = 0
        for m in pattern.finditer(sentencesString):
            sentences.append(sentencesString[lastEnd:m.start()])
            lastEnd = m.end()
        if lastEnd < len(sentencesString):
            sentences.append(sentencesString[lastEnd:])
        return sentences

    def countWords(self, sentence):
        cleaned = re.sub(r'[^a-zA-Z\s]', '', sentence)
        words = self._javaSplit(cleaned, r'\s+')
        return len(words)

    def _javaSplit(self, s, pattern):
        # Emulate Java's String.split(regex) behavior:
        # - leading empty strings are kept
        # - trailing empty strings are removed
        # - all-delimiter strings yield empty array
        if not s:
            return ['']
        if not s.strip():
            return []
        parts = re.split(pattern, s)
        while parts and parts[-1] == '':
            parts.pop()
        return parts

    def processTextFile(self, sentencesString):
        sentences = self.splitSentences(sentencesString)
        maxCount = 0
        for sentence in sentences:
            count = self.countWords(sentence)
            if count > maxCount:
                maxCount = count
        return maxCount