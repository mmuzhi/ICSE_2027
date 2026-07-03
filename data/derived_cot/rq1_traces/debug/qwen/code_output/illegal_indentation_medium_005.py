class Solution:
    def maximumNumber(self, num: str, change: List[int]) -> str:
        num_list = list(num)
        for i, ch in enumerate(num_list):
            x = int(ch)
            if x < change[x]:
                num_list[i] = str(change[x])
        return ''.join(num_list)