from collections import Counter

class Solution:
    def minSteps(self, s: str, t: str) -> int:
        cnt1 = Counter(s)
        cnt2 = Counter(t)
        cnt = cnt1 - cnt2  # characters that appear more in s than in t
        return sum(cnt.values())