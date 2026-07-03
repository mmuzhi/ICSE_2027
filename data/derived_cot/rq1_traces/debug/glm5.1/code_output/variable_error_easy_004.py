from typing import List

class Solution:
  def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:
    nums, sums, n = sorted(nums), [0], len(nums) + 1
    for num in nums:
      sums.append(sums[-1] + num)
    
    def bSearch(q, l=0, r=n):
      while l < r:
        mid = (l + r) >> 1
        if sums[mid] <= q:
          l = mid + 1
        else:
          r = mid
      return l - 1

    return [bSearch(q) for q in queries]