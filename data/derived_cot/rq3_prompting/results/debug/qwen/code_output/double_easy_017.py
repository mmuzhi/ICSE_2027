class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        count = {}
        for num in nums:
            count[num] = count.get(num, 0) + 1
        
        distinct_nums = sorted(count.keys())
        prefix_arr = []
        s = 0
        for num in distinct_nums:
            s += count[num]
            prefix_arr.append(s)
        
        res = []
        for num in nums:
            low, high = 0, len(distinct_nums)
            while low < high:
                mid = (low + high) // 2
                if distinct_nums[mid] < num:
                    low = mid + 1
                else:
                    high = mid
            idx = low
            if idx == 0:
                res.append(0)
            else:
                res.append(prefix_arr[idx-1])
        return res