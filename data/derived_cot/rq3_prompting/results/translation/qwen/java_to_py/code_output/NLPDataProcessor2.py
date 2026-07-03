import re
from typing import List, Dict, Tuple

class NLPDataProcessor2:

    class WordFrequency:
        def __init__(self, word: str, frequency: int):
            self.word = word
            self.frequency = frequency

        def __repr__(self):
            return f"WordFrequency{{word='{self.word}', frequency={self.frequency}}}"

        def __eq__(self, other):
            if not isinstance(other, type(self)):
                return NotImplemented
            return self.word == other.word and self.frequency == other.frequency

        def __hash__(self):
            return hash((self.word, self.frequency))

        @staticmethod
        def by_frequency_then_word():
            return lambda wf1, wf2: (
                (wf2.frequency - wf1.frequency) or
                (wf1.word.compareTo(wf2.word) if type(wf1.word) is str and type(wf2.word) is str else 0)
            )

    @staticmethod
    def _process_data_single_string(s: str) -> List[str]:
        cleaned = re.sub(r'[^a-zA-Z\s]', '', s.lower())
        return [] if cleaned == '' else cleaned.split()

    @staticmethod
    def processData(string_list: List[str]) -> List[List[str]]:
        return [NLPDataProcessor2._process_data_single_string(s) for s in string_list]

    @staticmethod
    def calculateWordFrequency(words_list: List[List[str]]) -> List['NLPDataProcessor2.WordFrequency']:
        frequency_map: Dict[str, int] = {}
        order_map: Dict[str, int] = {}
        index = 0
        
        for sublist in words_list:
            for word in sublist:
                if word not in frequency_map:
                    order_map[word] = index
                    index += 1
                frequency_map[word] = frequency_map.get(word, 0) + 1
        
        word_freqs = [
            NLPDataProcessor2.WordFrequency(word, count)
            for word, count in frequency_map.items()
            if count > 1 or word == "%%%"
        ]
        
        word_freqs.sort(key=lambda x: (-x.frequency, order_map[x.word]))
        return word_freqs

    @staticmethod
    def process(string_list: List[str]) -> List['NLPDataProcessor2.WordFrequency']:
        return NLPDataProcessor2.calculateWordFrequency(NLPDataProcessor2.processData(string_list))