from collections import Counter

class Solution:
    def minSteps(self, s: str, t: str) -> int:
        cnt1 = Counter(s)
        cnt2 = Counter(t)
        total = 0
        all_chars = set(cnt1.keys()) | set(cnt2.keys())
        for char in all_chars:
            total += abs(cnt1[char] - cnt2[char])
        return total // 2