class Solution:
    def findComplement(self, num: int) -> int:
        if num == 0:
            return 0
        n = num.bit_length()
        all_ones = (1 << n) - 1
        return all_ones ^ num