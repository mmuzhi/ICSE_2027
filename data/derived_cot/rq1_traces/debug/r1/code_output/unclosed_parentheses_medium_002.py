class Solution:
    def longestString(self, x: int, y: int, z: int) -> int:
        if x > y:
            x, y = y, x
        return (min(x + y, 2 * x + (1 if z else 0)) * 2) + 2 * z