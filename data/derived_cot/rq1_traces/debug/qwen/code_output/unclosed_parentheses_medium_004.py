from collections import defaultdict

class Solution:
    def numOfPairs(self, nums: List[str], target: str) -> int:
        d = defaultdict(int)
        for char in nums:
            d[char] += 1
            
        n = len(target)
        pairs = 0
        for i in range(1, n):
            part1 = target[:i]
            part2 = target[i:]
            if part1 in d and part2 in d:
                pairs += d[part1] * d[part2]
        return pairs