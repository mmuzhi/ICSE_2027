class Solution:
    def flipgame(self, fronts: List[int], backs: List[int]) -> int:
        bad = {i for i, j in zip(fronts, backs) if i == j}
        nums = set(fronts + backs)
        for i in sorted(nums):
            if i not in bad:
                return i
        return 0