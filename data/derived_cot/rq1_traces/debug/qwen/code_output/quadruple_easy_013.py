class Solution:
    def findComplement(self, num: int) -> int:
        if num == 0:
            return 0
        com = ''
        while num > 0:
            if num % 2 == 1:
                com += '1'
            else:
                com += '0'
            num = num // 2
        com = com[::-1]
        flipped_com = ''.join('0' if bit == '1' else '1' for bit in com)
        return int(flipped_com, 2)