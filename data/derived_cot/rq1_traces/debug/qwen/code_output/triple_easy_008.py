class Solution:
    def selfDividingNumbers(self, left: int, right: int) -> List[int]:
        res = []
        for i in range(left, right + 1):
            ch = True
            num_str = str(i)
            for j in num_str:
                if j == '0':
                    ch = False
                    break
                if i % int(j) != 0:
                    ch = False
                    break
            if ch:
                res.append(i)
        return res