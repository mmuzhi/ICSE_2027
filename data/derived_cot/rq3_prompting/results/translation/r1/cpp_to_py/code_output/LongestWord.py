import string

class LongestWord:
    def __init__(self):
        self.word_list = []

    def add_word(self, word):
        self.word_list.append(word)

    def find_longest_word(self, sentence):
        # Convert to lowercase
        lower_sentence = sentence.lower()
        # Remove punctuation
        translator = str.maketrans('', '', string.punctuation)
        lower_sentence = lower_sentence.translate(translator)
        # Split into words and find the longest matching word
        longest_word = ""
        for word in lower_sentence.split():
            if word in self.word_list and len(word) > len(longest_word):
                longest_word = word
        return longest_word

    def get_word_list(self):
        # Return a copy to preserve behavior (C++ returns by value)
        return self.word_list.copy()