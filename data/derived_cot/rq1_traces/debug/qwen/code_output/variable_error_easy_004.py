class Solution:
    def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        nums = sorted(nums)
        sums = [0]
        for num in nums:
            sums.append(sums[-1] + num)
        
        def bSearch(q):
            low, high = 0, len(sums) - 1
            while low <= high:
                mid = (low + high) // 2
                if sums[mid] <= q:
                    low = mid + 1
                else:
                    high = mid - 1
            return high
        
        return [bSearch(q) for q in queries]