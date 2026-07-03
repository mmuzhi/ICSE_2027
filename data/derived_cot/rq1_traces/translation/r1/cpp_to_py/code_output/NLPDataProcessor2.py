import re
import string
from collections import OrderedDict

allowed_chars = string.ascii_letters + string.whitespace

def remove_non_alpha(s):
    return ''.join(c for c in s if c in allowed_chars)

def to_lowercase(s):
    return s.lower()

class NLPDataProcessor2:
    def process_data(self, string_list):
        words_list = []
        for s in string_list:
            s_clean = remove_non_alpha(s)
            s_lower = to_lowercase(s_clean)
            words = [word for word in re.split(r'\s+', s_lower) if word != '']
            words_list.append(words)
        return words_list

    def calculate_word_frequency(self, words_list):
        word_frequency = {}
        first_appear = {}
        js = 0
        
        for words in words_list:
            for word in words:
                if word not in first_appear:
                    js += 1
                    first_appear[word] = js
                word_frequency[word] = word_frequency.get(word, 0) + 1
        
        items = list(word_frequency.items())
        sorted_items = sorted(items, key=lambda x: (-x[1], first_appear[x[0]]))
        
        top5 = sorted_items[:5]
        sorted_by_word = sorted(top5, key=lambda x: x[0])
        
        result_dict = OrderedDict()
        for word, freq in sorted_by_word:
            result_dict[word] = freq
            
        return result_dict

    def process(self, string_list):
        words_list = self.process_data(string_list)
        return self.calculate_word_frequency(words_list)