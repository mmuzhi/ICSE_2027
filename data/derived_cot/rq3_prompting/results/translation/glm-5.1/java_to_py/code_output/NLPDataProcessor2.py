import re

class WordFrequency:
    def __init__(self, word, frequency):
        self._word = word
        self._frequency = frequency

    @property
    def word(self):
        return self._word

    @property
    def frequency(self):
        return self._frequency

    def get_word(self):
        return self._word

    def get_frequency(self):
        return self._frequency

    def __str__(self):
        return f"WordFrequency{{word='{self._word}', frequency={self._frequency}}}"

    def __eq__(self, other):
        if self is other:
            return True
        if other is None or type(self) != type(other):
            return False
        return self._frequency == other._frequency and self._word == other._word

    def __hash__(self):
        return hash((self._word, self._frequency))

    @classmethod
    def by_frequency_then_word(cls):
        return lambda wf: (-wf.frequency, wf.word)


class NLPDataProcessor2:
    def process_data(self, string_list):
        words_list = []
        pattern = re.compile(r'[^a-zA-Z\s]')
        for string in string_list:
            processed_string = pattern.sub('', string.lower())
            if not processed_string:
                words = []
            else:
                words = re.split(r'\s+', processed_string)
                # Mimic Java's split behavior which removes trailing empty strings
                while words and words[-1] == '':
                    words.pop()
            words_list.append(words)
        return words_list

    def calculate_word_frequency(self, words_list):
        frequency_map = {}
        order_map = {}
        index = 0

        for words in words_list:
            for word in words:
                if word not in frequency_map:
                    order_map[word] = index
                    index += 1
                frequency_map[word] = frequency_map.get(word, 0) + 1

        word_frequencies = []
        for word, frequency in frequency_map.items():
            if frequency > 1 or word == "%%%":
                word_frequencies.append(WordFrequency(word, frequency))

        word_frequencies.sort(key=lambda wf: (-wf.frequency, order_map[wf.word]))
        return word_frequencies

    def process(self, string_list):
        words_list = self.process_data(string_list)
        return self.calculate_word_frequency(words_list)