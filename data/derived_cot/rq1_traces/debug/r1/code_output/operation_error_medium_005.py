class Solution:
    def findLongestWord(self, s: str, d: List[str]) -> str:
        res = ''
        for cand in d:
            if self.is_subsequence(s, cand) and (len(cand) > len(res) or (len(cand) == len(res) and cand < res)):
                res = cand
        return res
    
    def is_subsequence(self, s: str, d: str) -> bool:
        i, j = 0, 0
        while i < len(s) and j < len(d):
            if s[i] == d[j]:
                j += 1
            i += 1
        return j == len(d)