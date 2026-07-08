import string

class LongestWord:
    def __init__(self):
        self.word_list = []

    def add_word(self, word: str) -> None:
        self.word_list.append(word)

    def find_longest_word(self, sentence: str) -> str:
        # Convert to lowercase
        lower_sentence = sentence.lower()
        
        # Remove punctuation (equivalent to std::ispunct in C locale)
        translator = str.maketrans('', '', string.punctuation)
        lower_sentence = lower_sentence.translate(translator)
        
        # Split by whitespace (equivalent to std::istringstream >> word)
        words = lower_sentence.split()
        
        # Find the longest word that exists in the word_list
        longest_word = ""
        for word in words:
            # `word in self.word_list` behaves like std::find != end
            if word in self.word_list and len(word) > len(longest_word):
                longest_word = word
                
        return longest_word

    def get_word_list(self) -> list:
        # Return a copy to mimic C++ returning by value (prevents external mutation)
        return list(self.word_list)