from collections import defaultdict
from typing import List

class Solution:
    def numOfPairs(self, nums: List[str], target: str) -> int:
        d = defaultdict(int)
        for s in nums:
            d[s] += 1

        arr = list(target)
        pairs = 0
        num = ""
        while len(arr) > 1:
            num += arr.pop()
            findNum = "".join(arr)
            suffix = num[::-1]
            if suffix not in d or findNum not in d:
                continue
            c1 = d[suffix]
            d[suffix] -= 1
            c2 = d[findNum]
            d[suffix] += 1
            pairs += c1 * c2
        return pairs