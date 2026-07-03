from collections import defaultdict

class Solution:
    def numOfPairs(self, nums: List[str], target: str) -> int:
        d = defaultdict(int)
        for char in nums:
            d[char] += 1
        
        pairs = 0
        for s in d:
            if len(s) > len(target):
                continue
            if target.startswith(s):
                t1 = target[len(s):]
                if t1 in d:
                    pairs += d[s] * d[t1]
        return pairs