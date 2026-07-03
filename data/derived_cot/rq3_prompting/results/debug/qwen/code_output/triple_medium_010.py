class Solution:
    def minFlips(self, a: int, b: int, c: int) -> int:
        if (a | b) == c:
            return 0
        
        c_bin = bin(c)[2:].zfill(32)
        a_bin = bin(a)[2:].zfill(32)
        b_bin = bin(b)[2:].zfill(32)
        
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