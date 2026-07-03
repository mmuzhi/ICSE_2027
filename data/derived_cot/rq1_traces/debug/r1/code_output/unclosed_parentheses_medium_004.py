from collections import defaultdict
from typing import List

class Solution:
    def numOfPairs(self, nums: List[str], target: str) -> int:
        d = defaultdict(int)
        for num in nums:
            d[num] += 1
            
        arr = list(target)
        pairs = 0
        num_str = ""
        while len(arr) > 1:
            num_str += arr.pop()
            suffix = num_str[::-1]
            prefix = ''.join(arr)
            if suffix in d and prefix in d:
                c1 = d[suffix]
                d[suffix] -= 1  # Temporarily decrement to avoid same element
                c2 = d[prefix]
                d[suffix] += 1  # Restore the count
                pairs += c1 * c2
        return pairs