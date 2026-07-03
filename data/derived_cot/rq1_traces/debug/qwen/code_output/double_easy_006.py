from collections import Counter

class Solution:
    def uniqueOccurrences(self, arr: List[int]) -> bool:
        d = Counter(arr)
        freqs = list(d.values())
        return len(freqs) == len(set(freqs))