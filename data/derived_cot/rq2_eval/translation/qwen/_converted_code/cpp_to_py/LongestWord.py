import string
from typing import List

class LongestWord:
    def __init__(self):
        self.word_list: List[str] = []

    def add_word(self, word: str) -> None:
        self.word_list.append(word)

    def find_longest_word(self, sentence: str) -> str:
        # Convert the sentence to lowercase
        clean_sentence = sentence.lower()
        # Remove punctuation
        clean_sentence = clean_sentence.translate(str.maketrans('', '', string.punctuation))
        # Split the sentence into words
        words = clean_sentence.split()
        longest_word = ""
        for word in words:
            if word in self.word_list and len(word) > len(longest_word):
                longest_word = word
        return longest_word

    def get_word_list(self) -> List[str]:
        return self.word_list