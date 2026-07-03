import re

class LongestWord:

    def __init__(self):
        self.wordList = []

    def add_word(self, word):
        self.wordList.append(word)

    def find_longest_word(self, sentence):
        bad_chars = '!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~'
        pattern = re.escape(bad_chars)
        sentence = re.sub(f'[{pattern}]', '', sentence)
        words = sentence.split()
        longest_word = ''
        for word in words:
            if word in self.wordList and len(word) > len(longest_word):
                longest_word = word
        return longest_word