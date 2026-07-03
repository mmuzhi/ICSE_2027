class Solution:
    def thirdMax(self, nums) -> int:
        unique = set(nums)
        if len(unique) < 3:
            return max(unique)
        else:
            sorted_unique = sorted(unique, reverse=True)
            return sorted_unique[2]