import re

class NLPDataProcessor2:
    def __init__(self):
        self.first_appear = {}
    
    @staticmethod
    def to_lowercase(s):
        return s.lower()
    
    @staticmethod
    def remove_non_alpha(s):
        return ''.join([c for c in s if c.isalpha() or c.isspace()])
    
    def process_data(self, string_list):
        words_list = []
        pattern = r'\s+'
        
        for str_val in string_list:
            processed_string = self.to_lowercase(self.remove_non_alpha(str_val))
            tokens = re.findall(pattern, processed_string)
            words = [token for token in tokens if token]
            words_list.append(words)
            
        return words_list

    def calculate_word_frequency(self, words_list):
        self.first_appear.clear()
        word_frequency = {}
        js = 0
        
        for words in words_list:
            for word in words:
                if word not in word_frequency:
                    self.first_appear[word] = js
                    js += 1
                word_frequency[word] += 1
                
        if not word_frequency:
            return {}
            
        sorted_items = sorted(word_frequency.items(), key=lambda x: (-x[1], self.first_appear[x[0]]))
        top_5 = {}
        for i in range(min(5, len(sorted_items))):
            word, count = sorted_items[i]
            top_5[word] = count
            
        return top_5

    def process(self, string_list):
        words_list = self.process_data(string_list)
        return self.calculate_word_frequency(words_list)