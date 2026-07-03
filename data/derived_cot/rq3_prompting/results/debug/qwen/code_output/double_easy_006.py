from collections import Counter
class Solution:
    def uniqueOccurrences(self, arr: List[int]) -> bool:
        d = Counter(arr)
        if len(d) == len(set(d.values())):
            return True
        else:
            return False