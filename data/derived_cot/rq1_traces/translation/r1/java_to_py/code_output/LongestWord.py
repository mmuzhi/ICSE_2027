import re

class LongestWord:
    def __init__(self):
        self.wordList = []
    
    def addWord(self, word):
        self.wordList.append(word)
    
    def findLongestWord(self, sentence):
        longest_word = ""
        sentence = sentence.lower()
        punctuation_pattern = r"[\"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~]"
        sentence = re.sub(punctuation_pattern, '', sentence)
        words = sentence.split()
        for word in words:
            if word in self.wordList and len(word) > len(longest_word):
                longest_word = word
        return longest_word

if __name__ == "__main__":
    lw = LongestWord()
    lw.addWord("A")
    lw.addWord("aM")
    print(lw.findLongestWord("I am a student."))