from collections import Counter
class Solution:
    def uniqueOccurrences(self, arr: List[int]) -> bool:
        d = Counter(arr)
        l = list(d.values())
        print(l)
        if len(l) == len(set(l)):
            return True
        else:
            return False