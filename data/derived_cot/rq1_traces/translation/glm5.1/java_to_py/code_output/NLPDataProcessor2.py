import re


class WordFrequency:
    __slots__ = ('word', 'frequency')

    def __init__(self, word, frequency):
        self.word = word
        self.frequency = frequency

    def get_word(self):
        return self.word

    def get_frequency(self):
        return self.frequency

    def __str__(self):
        return f"WordFrequency{{word='{self.word}', frequency={self.frequency}}}"

    def __repr__(self):
        return self.__str__()

    def __eq__(self, other):
        if self is other:
            return True
        if other is None or type(self) is not type(other):
            return False
        return self.frequency == other.frequency and self.word == other.word

    def __hash__(self):
        return hash((self.word, self.frequency))

    @staticmethod
    def by_frequency_then_word():
        """Returns a key function for sorting by frequency descending, then word ascending."""
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
                # Match Java's String.split behavior: remove trailing empty strings
                while words and words[-1] == '':
                    words.pop()
            words_list.append(words)
        return words_list

    def calculate_word_frequency(self, words_list):
        frequency_map = {}  # Preserves insertion order (Python 3.7+), matching LinkedHashMap
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