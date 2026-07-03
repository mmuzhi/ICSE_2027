class Solution:
    def selfDividingNumbers(self, left: int, right: int) -> List[int]:
        res = []
        for i in range(left, right + 1):
            is_self_dividing = True
            for j in str(i):
                if j == '0' or i % int(j) != 0:
                    is_self_dividing = False
                    break
            if is_self_dividing:
                res.append(i)
        return res