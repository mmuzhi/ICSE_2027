from collections import defaultdict

class Solution:
    def arrayChange(self, nums: List[int], operations: List[List[int]]) -> List[int]:
        d = defaultdict(set)
        for i, num in enumerate(nums):
            d[num].add(i)
        
        for op in operations:
            old_val, new_val = op
            if old_val == new_val:
                continue
            if old_val not in d:
                continue
            indices = d.pop(old_val)
            for idx in indices:
                nums[idx] = new_val
            if new_val in d:
                d[new_val] |= indices
            else:
                d[new_val] = indices
        
        return nums