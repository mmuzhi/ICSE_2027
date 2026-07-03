class Solution:
    def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        nums = sorted(nums)
        sums = [0]
        for num in nums:
            sums.append(sums[-1] + num)
        n = len(sums)
        
        def bSearch(q, l=0, mid=(len(sums)>>1), r=len(sums)):
            while l < mid < r:
                if sums[mid] > q:
                    r = mid
                elif sums[mid] < q:
                    l = mid
                else:
                    break
                mid = (l + r) >> 1
            return mid
        
        return [bSearch(q) for q in queries]