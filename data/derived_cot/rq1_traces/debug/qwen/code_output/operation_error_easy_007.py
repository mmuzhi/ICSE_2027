class Solution:
    def findComplement(self, num: int) -> int:
        if num == 0:
            return 0
        n = num.bit_length()
        s = bin(num)[2:]
        comp_str = ''.join('1' if bit == '0' else '0' for bit in s)
        return int(comp_str, 2)