class Solution:
    def getLastMoment(self, n: int, left: List[int], right: List[int]) -> int:
        left_max = n/2 - (left[0] if left else 0)
        right_max = (right[0] if right else 0) - n/2
        return max(left_max, right_max)