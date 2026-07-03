import re
from typing import List, Dict, Tuple

class NLPDataProcessor2:
    class WordFrequency:
        def __init__(self, word: str, frequency: int):
            self.word = word
            self.frequency = frequency

        def get_word(self) -> str:
            return self.word

        def get_frequency(self) -> int:
            return self.frequency

        def __repr__(self) -> str:
            return f"WordFrequency{{word='{self.word}', frequency={self.frequency}}}"

        def __eq__(self, other) -> bool:
            if not isinstance(other, NLPDataProcessor2.WordFrequency):
                return False
            return self.word == other.word and self.frequency == other.frequency

        def __hash__(self) -> int:
            return hash((self.word, self.frequency))

        @staticmethod
        def by_frequency_then_word():
            # Returns a key function for sorting: descending frequency, then ascending word.
            return lambda wf: (-wf.frequency, wf.word)

    def process_data(self, string_list: List[str]) -> List[List[str]]:
        words_list: List[List[str]] = []
        pattern = re.compile(r'[^a-zA-Z\s]')
        for s in string_list:
            processed = pattern.sub('', s.lower())
            if not processed:
                words_list.append([])
            else:
                words_list.append(processed.split())
        return words_list

    def calculate_word_frequency(self, words_list: List[List[str]]) -> List[WordFrequency]:
        frequency_map: Dict[str, int] = {}
        order_map: Dict[str, int] = {}
        index = 0

        for words in words_list:
            for word in words:
                if word not in frequency_map:
                    order_map[word] = index
                    index += 1
                frequency_map[word] = frequency_map.get(word, 0) + 1

        word_frequencies: List[NLPDataProcessor2.WordFrequency] = []
        for word, freq in frequency_map.items():
            if freq > 1 or word == '%%%':
                word_frequencies.append(NLPDataProcessor2.WordFrequency(word, freq))

        # Sort: descending frequency, then ascending order of first appearance.
        word_frequencies.sort(key=lambda wf: (-wf.frequency, order_map[wf.word]))
        return word_frequencies

    def process(self, string_list: List[str]) -> List[WordFrequency]:
        words_list = self.process_data(string_list)
        return self.calculate_word_frequency(words_list)