from collections import Counter

class Solution:
    def minSteps(self, s: str, t: str) -> int:
        cnt_s = Counter(s)
        cnt_t = Counter(t)
        ans = 0
        for char in cnt_t:
            if char in cnt_s:
                ans += max(0, cnt_t[char] - cnt_s[char])
            else:
                ans += cnt_t[char]
        return ans