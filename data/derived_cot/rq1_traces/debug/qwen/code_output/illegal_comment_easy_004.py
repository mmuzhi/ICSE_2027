class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        count_dict = {}
        for num in nums:
            count_dict[num] = count_dict.get(num, 0) + 1
        
        distinct_nums = sorted(count_dict.keys())
        
        res = []
        for num in nums:
            total = 0
            for d in distinct_nums:
                if d < num:
                    total += count_dict[d]
                else:
                    break
            res.append(total)
        
        return res