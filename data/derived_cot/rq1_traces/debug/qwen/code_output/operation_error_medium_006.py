from collections import Counter

class Solution:
    def wordSubsets(self, words1: List[str], words2: List[str]) -> List[str]:
        max_freq = {}
        for word in words2:
            freq = Counter(word)
            for letter, count in freq.items():
                if letter not in max_freq or count > max_freq[letter]:
                    max_freq[letter] = count
        required = Counter(max_freq)
        
        return [w1 for w1 in words1 if Counter(w1) >= required]