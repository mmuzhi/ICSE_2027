class BoyerMooreSearch:
    def __init__(self, text, pattern):
        self.text = text
        self.pattern = pattern
        self.textLen = len(text)
        self.patLen = len(pattern)
    
    def matchInPattern(self, ch):
        for i in range(self.patLen-1, -1, -1):
            if self.pattern[i] == ch:
                return i
        return -1

    def mismatchInText(self, currentPos):
        for i in range(self.patLen-1, -1, -1):
            if self.text[currentPos + i] != self.pattern[i]:
                return currentPos + i
        return -1

    def badCharacterHeuristic(self):
        badCharHeuristic = {}
        for j in range(self.patLen):
            badCharHeuristic[self.pattern[j]] = j
        
        if self.patLen == 0:
            return list(range(0, self.textLen + 1))
        
        positions = []
        i = 0
        while i <= self.textLen - self.patLen:
            mismatchIndex = self.mismatchInText(i)
            if mismatchIndex == -1:
                positions.append(i)
                i += self.patLen
            else:
                mismatchChar = self.text[mismatchIndex]
                matchIndex = badCharHeuristic.get(mismatchChar, -1)
                if matchIndex >= 0:
                    shift = mismatchIndex - i - matchIndex
                    if shift < 1:
                        shift = 1
                    i += shift
                else:
                    shift = mismatchIndex - i + 1
                    i += shift
        
        return positions