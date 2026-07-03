class Solution:
    def checkAlmostEquivalent(self, word1: str, word2: str) -> bool:
        A = [0] * 26
        B = [0] * 26
        for char in word1:
            idx = ord(char) - ord('a')
            A[idx] += 1
        for char in word2:
            idx = ord(char) - ord('a')
            B[idx] += 1
        for i in range(26):
            if abs(A[i] - B[i]) > 3:
                return False
        return True