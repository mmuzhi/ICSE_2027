from collections import defaultdict

class Solution:
    def findLHS(self, nums: List[int]) -> int:
        count_map = defaultdict(int)
        for num in nums:
            count_map[num] += 1
        
        result = 0
        for num in count_map:
            if num + 1 in count_map:
                candidate = count_map[num] + count_map[num + 1]
            else:
                candidate = count_map[num]
            if candidate > result:
                result = candidate
        return result