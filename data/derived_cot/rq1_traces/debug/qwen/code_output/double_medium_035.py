class Solution:
    def maximumNumber(self, num: str, change: List[int]) -> str:
        num_list = list(num)
        on = False
        for i, ch in enumerate(num_list):
            x = int(ch)
            if x < change[x]:
                on = True
                num_list[i] = str(change[x])
            elif x > change[x] and on:
                break
        return "".join(num_list)