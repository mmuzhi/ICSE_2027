class Solution:
    def areAlmostEqual(self, s1: str, s2: str) -> bool:
        if len(s1) != len(s2):
            return False
        if s1 == s2:
            return True
        diff_indices = []
        for i in range(len(s1)):
            if s1[i] != s2[i]:
                diff_indices.append(i)
        if len(diff_indices) != 2:
            return False
        i, j = diff_indices
        return s1[i] == s2[j] and s1[j] == s2[i]