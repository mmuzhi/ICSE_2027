class Solution:
    def minFlips(self, a: int, b: int, c: int) -> int:
        if (a | b) == c:
            return 0
        c_bin = ('0' * 32 + bin(c)[2:])[-32:]
        a_bin = ('0' * 32 + bin(a)[2:])[-32:]
        b_bin = ('0' * 32 + bin(b)[2:])[-32:]

        cnt = 0
        for i in range(32):
            if c_bin[i] == '0':
                if a_bin[i] == '1':
                    cnt += 1
                if b_bin[i] == '1':
                    cnt += 1
            else:
                if a_bin[i] == '0' and b_bin[i] == '0':
                    cnt += 1
        return cnt