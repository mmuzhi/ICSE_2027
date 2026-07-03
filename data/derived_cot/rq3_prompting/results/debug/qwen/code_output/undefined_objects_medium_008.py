from collections import defaultdict

class Solution:
    def arrayChange(self, nums: List[int], operations: List[List[int]]) -> List[int]:
        index_map = defaultdict(list)
        for i, n in enumerate(nums):
            index_map[n].append(i)
        
        for op in operations:
            n1, n2 = op
            if n1 in index_map:
                indices = index_map.pop(n1)
                for i in indices:
                    nums[i] = n2
                if n2 in index_map:
                    index_map[n2].extend(indices)
                else:
                    index_map[n2] = indices
        
        return nums