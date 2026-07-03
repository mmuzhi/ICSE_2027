class Solution:
  def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:
    nums, sums, res, n = sorted(nums), [0], [], len(nums)+1
    for num in nums:
      sums.append(sums[-1] + num)
    
    def bSearch(q):
      l, r = 0, n - 1
      while l < r:
        mid = (l + r + 1) >> 1
        if sums[mid] <= q:
          l = mid
        else:
          r = mid - 1
      return l

    return [bSearch(q) for q in queries]