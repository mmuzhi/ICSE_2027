class Solution:
    def maximumNumber(self, num: str, change: List[int]) -> str:
        original = list(num)
        num_list = list(num)
        on = False
        for i, ch in enumerate(original):
            x = int(ch)
            if not on:
                if change[x] > x:
                    num_list[i] = str(change[x])
                    on = True
            else:
                if change[x] > x:
                    num_list[i] = str(change[x])
                else:
                    break
        return "".join(num_list)