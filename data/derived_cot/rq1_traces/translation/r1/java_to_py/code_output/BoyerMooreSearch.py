class BoyerMooreSearch:
    def __init__(self, text, pattern):
        self.text = text
        self.pattern = pattern
        self.textLen = len(text)
        self.patLen = len(pattern)
    
    def mismatchInText(self, currentPos):
        for j in range(self.patLen - 1, -1, -1):
            if self.pattern[j] != self.text[currentPos + j]:
                return currentPos + j
        return -1

    def badCharacterHeuristic(self):
        patLen = self.patLen
        textLen = self.textLen
        if patLen == 0:
            return list(range(textLen + 1))
        
        badChar = {}
        for idx, char in enumerate(self.pattern):
            badChar[char] = idx
        
        positions = []
        i = 0
        while i <= textLen - patLen:
            mismatchIndex = self.mismatchInText(i)
            if mismatchIndex == -1:
                positions.append(i)
                i += patLen
            else:
                j = mismatchIndex - i
                char_text = self.text[mismatchIndex]
                matchIndex = badChar.get(char_text, -1)
                if matchIndex >= 0:
                    shift = j - matchIndex
                    i += max(1, shift)
                else:
                    i = mismatchIndex + 1
        return positions