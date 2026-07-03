from functools import reduce

class Solution:
    def numberOfGoodSubarraySplits(self, nums: List[int]) -> int:
        if nums[0] != nums[-1] or nums[0] not in nums:
            return 0
        
        s = ''.join(map(str, nums)).strip('0')
        parts = s.split(str(nums[0]))
        
        if not parts[0]:
            parts = parts[1:]
        if not parts[-1]:
            parts = parts[:-1]
        
        ways = [len(part) + 1 for part in parts]
        
        result = reduce(lambda a, b: a * b, ways, 1) % 1000000007
        return result