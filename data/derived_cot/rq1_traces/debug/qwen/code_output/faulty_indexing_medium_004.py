class Solution:
    def getLastMoment(self, n: int, left: List[int], right: List[int]) -> int:
        left_time = n - min(left) if left else 0
        right_time = max(right) if right else 0
        return max(left_time, right_time)