from collections import Counter

class Solution:
    def uniqueOccurrences(self, arr):
        d = Counter(arr)
        l = list(d.values())
        if len(l) == len(set(l)):
            return True
        else:
            return False