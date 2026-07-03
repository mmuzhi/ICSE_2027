class Solution:
    def thirdMax(self, nums: List[int]) -> int:
        unique = list(set(nums))
        return max(unique) if len(unique) < 3 else sorted(unique)[-3]