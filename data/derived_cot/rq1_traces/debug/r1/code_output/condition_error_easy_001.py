class Solution:
    def thirdMax(self, nums: List[int]) -> int:
        unique = set(nums)
        return sorted(unique)[-3] if len(unique) >= 3 else max(unique)