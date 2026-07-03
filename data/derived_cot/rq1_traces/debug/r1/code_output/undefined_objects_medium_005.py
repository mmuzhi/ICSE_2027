from collections import Counter

class Solution:
    def minSteps(self, s: str, t: str) -> int:
        cnt1 = Counter(s)
        cnt2 = Counter(t)
        cnt = (cnt1 - cnt2) + (cnt2 - cnt1)
        return sum(cnt.values()) // 2