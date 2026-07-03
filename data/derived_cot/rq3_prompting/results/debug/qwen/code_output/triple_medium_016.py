class Solution:
    def maximumNumber(self, num: str, change: List[int]) -> str:
        num_list = list(num)
        can_change = True
        for i in range(len(num_list)):
            x = int(num_list[i])
            if can_change and change[x] > x:
                num_list[i] = str(change[x])
            else:
                can_change = False
        return "".join(num_list)