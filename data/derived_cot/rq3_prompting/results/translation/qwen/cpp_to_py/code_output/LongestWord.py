import string

class LongestWord:
    def __init__(self):
        self.word_list = []
    
    def add_word(self, word):
        self.word_list.append(word)
    
    def find_longest_word(self, sentence):
        # Convert the sentence to lowercase
        sentence_lower = sentence.lower()
        
        # Remove punctuation using str.maketrans
        translator = str.maketrans('', '', string.punctuation)
        cleaned_sentence = sentence_lower.translate(translator)
        
        # Split the cleaned sentence into words
        words = cleaned_sentence.split()
        
        longest_word = ''
        for word in words:
            if word in self.word_list and len(word) > len(longest_word):
                longest_word = word
        
        return longest_word
    
    def get_word_list(self):
        return self.word_list