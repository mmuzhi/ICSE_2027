from collections import Counter

class Solution:
    def minSteps(self, s: str, t: str) -> int:
        cnt1 = Counter(s)
        cnt2 = Counter(t)
        sm = 0
        for char in cnt2:
            if cnt2[char] > cnt1.get(char, 0):
                sm += (cnt2[char] - cnt1.get(char, 0))
        return sm