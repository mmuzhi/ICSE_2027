class Solution:
    def findLHS(self, nums: List[int]) -> int:
        from collections import defaultdict
        freq = defaultdict(int)
        for num in nums:
            freq[num] += 1
        
        result = 0
        for num in freq:
            if num + 1 in freq:
                result = max(result, freq[num] + freq[num + 1])
            if num - 1 in freq:
                result = max(result, freq[num] + freq[num - 1])
        return result