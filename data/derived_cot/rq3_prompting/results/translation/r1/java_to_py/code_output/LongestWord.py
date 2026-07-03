import re


class LongestWord:
    def __init__(self):
        self.word_list = []

    def add_word(self, word: str) -> None:
        self.word_list.append(word)

    def find_longest_word(self, sentence: str) -> str:
        longest_word = ""
        sentence = sentence.lower()
        # punctuation as in the Java code (Pattern.quote ensures literal interpretation)
        punctuation = r'!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~'
        pattern = '[' + re.escape(punctuation) + ']'
        sentence = re.sub(pattern, '', sentence)
        words = sentence.split(' ')
        for word in words:
            if word in self.word_list and len(word) > len(longest_word):
                longest_word = word
        return longest_word


if __name__ == '__main__':
    longest_word = LongestWord()
    longest_word.add_word("A")
    longest_word.add_word("aM")
    print(longest_word.find_longest_word("I am a student."))