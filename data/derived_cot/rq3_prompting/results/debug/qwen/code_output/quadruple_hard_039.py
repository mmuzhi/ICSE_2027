class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        tree = None
        ans = []
        for i, x in enumerate(nums):
            tree = insert(tree, x)
            if size(tree) > k:
                tree = remove(tree, nums[i - k + 1])
            if size(tree) == k:
                if k % 2 == 1:
                    ans.append(get(tree, k // 2 + 1))
                else:
                    a = get(tree, k//2)
                    b = get(tree, k//2+1)
                    ans.append((a + b) / 2.0)
        return ans