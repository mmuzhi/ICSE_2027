class Solution:
    def maximumNumber(self, num: str, change: List[int]) -> str:
        num = list(num)
        on = False 
        for i, ch in enumerate(num): 
            x = int(ch)
            if on:
                if change[x] < x:
                    break
                num[i] = str(change[x])
            else:
                if change[x] > x:
                    num[i] = str(change[x])
                    on = True
        return "".join(num)