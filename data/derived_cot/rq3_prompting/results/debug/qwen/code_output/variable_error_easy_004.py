class Solution:
    def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        nums.sort()
        sums = [0]
        for num in nums:
            sums.append(sums[-1] + num)
        
        def bSearch(q):
            low, high = 0, len(sums)
            while low < high:
                mid = (low + high) // 2
                if sums[mid] < q:
                    low = mid + 1
                else:
                    high = mid
            return low
        
        return [bSearch(q) for q in queries]