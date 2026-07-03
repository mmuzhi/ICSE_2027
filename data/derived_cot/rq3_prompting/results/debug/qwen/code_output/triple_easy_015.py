class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        s = set(nums)
        ans = None
        for num in nums:
            if num > 0 and -num not in s:
                if ans is None or num > ans:
                    ans = num
        return ans if ans is not None else -1