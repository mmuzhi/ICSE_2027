class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        count = [0] * 101
        res = []
        for num in nums:
            count[num] += 1 
        prefix = [0] * 101
        cumulative = 0
        for i in range(101):
            prefix[i] = cumulative
            cumulative += count[i]
        for num in nums:
            res.append(prefix[num])
        return res