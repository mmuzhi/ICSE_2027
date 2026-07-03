from collections import Counter

class Solution:
    def minSteps(self, s: str, t: str) -> int:
        cnt1 = Counter(s)
        cnt2 = Counter(t)
        return sum(max(0, cnt2[char] - cnt1[char]) for char in cnt2)