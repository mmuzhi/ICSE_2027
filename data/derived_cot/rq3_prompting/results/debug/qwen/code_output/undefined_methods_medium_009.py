class Solution:
    def partitionLabels(self, s: str) -> List[int]:
        last_occurrence = {char: idx for idx, char in enumerate(s)}
        n = len(s)
        start = 0
        max_last = 0
        ans = []
        for i in range(n):
            if i > max_last:
                ans.append(max_last - start + 1)
                start = i
                max_last = i
            else:
                if last_occurrence[s[i]] > max_last:
                    max_last = last_occurrence[s[i]]
        ans.append(max_last - start + 1)
        return ans