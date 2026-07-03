from collections import Counter

class Solution:
    def isTransformable(self, s: str, t: str) -> bool:
        return Counter(s) == Counter(t)