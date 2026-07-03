import re

class NLPDataProcessor2:

    class WordFrequency:
        __slots__ = ('word', 'frequency')

        def __init__(self, word, frequency):
            self.word = word
            self.frequency = frequency

        def __eq__(self, other):
            if self is other:
                return True
            if not isinstance(other, NLPDataProcessor2.WordFrequency):
                return False
            return self.frequency == other.frequency and self.word == other.word

        def __hash__(self):
            return hash((self.word, self.frequency))

        def __str__(self):
            return f"WordFrequency{{word='{self.word}', frequency={self.frequency}}}"

        @staticmethod
        def byFrequencyThenWord():

            def comparator(wf1, wf2):
                if wf1.frequency != wf2.frequency:
                    return wf2.frequency - wf1.frequency
                return (wf1.word > wf2.word) - (wf1.word < wf2.word)
            return comparator

    def process_data(self, stringList):
        pattern = re.compile('[^a-zA-Z\\s]')
        words_list = []
        for s in stringList:
            processed = pattern.sub('', s.lower())
            if processed == '':
                words = []
            else:
                words = re.split('\\s+', processed)
                while words and words[-1] == '':
                    words.pop()
            words_list.append(words)
        return words_list

    def calculate_word_frequency(self, wordsList):
        frequency_map = {}
        order_map = {}
        index = 0
        for words in wordsList:
            for word in words:
                if word not in frequency_map:
                    frequency_map[word] = 0
                    order_map[word] = index
                    index += 1
                frequency_map[word] += 1
        word_frequencies = []
        for word, freq in frequency_map.items():
            if freq > 1 or word == '%%%':
                word_frequencies.append(self.WordFrequency(word, freq))
        word_frequencies.sort(key=lambda wf: (-wf.frequency, order_map[wf.word]))
        return word_frequencies

    def process(self, stringList):
        wordsList = self.process_data(stringList)
        return self.calculate_word_frequency(wordsList)