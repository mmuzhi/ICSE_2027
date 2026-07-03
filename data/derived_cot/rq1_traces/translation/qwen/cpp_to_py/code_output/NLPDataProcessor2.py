import re
import locale
from collections import OrderedDict

def to_lowercase(str):
    try:
        locale.nl_langinfo(locale.CC)
    except:
        pass
    loc = locale.getlocale()
    if loc is None:
        # Use default if locale is not set
        return str.lower()
    try:
        return str.translate(str.maketrans('', '', ''), loc[0]).lower()
    except Exception:
        return str.lower()

def remove_non_alpha(str):
    try:
        locale.nl_langinfo(locale.CC)
    except:
        pass
    loc = locale.getlocale()
    if loc is None:
        return ''.join(filter(str.isalnum, str))
    try:
        return ''.join(c for c in str if locale.strcoll(c, '') and c.isspace() or locale.strcoll(c, '') and c.isalpha())
    except Exception:
        return ''.join(c for c in str if c.isalnum() or c.isspace())

class NLPDataProcessor2:
    @staticmethod
    def process_data(string_list):
        words_list = []
        for s in string_list:
            processed_string = remove_non_alpha(s)
            if processed_string.strip():
                words = [word for word in processed_string.split() if word]
                words_list.append(words)
            else:
                words_list.append([])
        return words_list

    @staticmethod
    def calculate_word_frequency(words_list):
        first_appear = {}
        word_frequency = {}
        js = 0
        for words in words_list:
            for word in words:
                if word not in word_frequency:
                    first_appear[word] = js + 1
                    word_frequency[word] = 0
                word_frequency[word] += 1
        sorted_items = sorted(word_frequency.items(), key=lambda x: (-x[1], first_appear[x[0]]))
        top_5 = OrderedDict()
        for i in range(min(5, len(sorted_items))):
            top_5[sorted_items[i][0]] = sorted_items[i][1]
        return top_5

    @staticmethod
    def process(string_list):
        words_list = NLPDataProcessor2.process_data(string_list)
        return NLPDataProcessor2.calculate_word_frequency(words_list)