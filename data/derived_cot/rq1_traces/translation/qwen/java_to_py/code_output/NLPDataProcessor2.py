import re
from collections import OrderedDict

class NLPDataProcessor2:

    class WordFrequency:
        def __init__(self, word, frequency):
            self.word = word
            self.frequency = frequency

        def __str__(self):
            return f"WordFrequency{{word='{self.word}', frequency={self.frequency}}}"

        def __eq__(self, other):
            if not isinstance(other, NLPDataProcessor2.WordFrequency):
                return False
            return self.word == other.word and self.frequency == other.frequency

        def __hash__(self):
            return hash((self.word, self.frequency))

        @classmethod
        def by_frequency_then_word(cls):
            return lambda x, y: (
                y.frequency - x.frequency or cls.word_order(x.word, y.word)
            )

        @staticmethod
        def word_order(word1, word2):
            return (ord(word1) if word1 else float('inf')) - (ord(word2) if word2 else float('inf'))

    def process_data(self, string_list):
        pattern = re.compile(r'[^a-zA-Z\s]')
        words_list = []
        for s in string_list:
            processed = pattern.sub('', s.lower())
            words = processed.split() if processed else []
            words_list.append(words)
        return words_list

    def calculate_word_frequency(self, words_list):
        frequency_map = OrderedDict()
        order_map = OrderedDict()
        index = 0
        for words in words_list:
            for word in words:
                if word not in order_map:
                    order_map[word] = index
                    index += 1
                frequency_map[word] = frequency_map.get(word, 0) + 1

        word_frequencies = []
        for word, freq in frequency_map.items():
            if freq > 1 or word == "%%%":
                word_frequencies.append(NLPDataProcessor2.WordFrequency(word, freq))

        word_frequencies.sort(key=lambda wf: (-wf.frequency, order_map[wf.word]))
        return word_frequencies

    def process(self, string_list):
        words_list = self.process_data(string_list)
        return self.calculate_word_frequency(words_list)