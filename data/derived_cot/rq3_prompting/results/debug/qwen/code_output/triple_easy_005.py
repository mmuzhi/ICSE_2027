class Solution:
    def checkAlmostEquivalent(self, word1: str, word2: str) -> bool:
        diff = [0] * 26
        for char in word1:
            diff[ord(char) - ord('a')] += 1
        for char in word2:
            diff[ord(char) - ord('a')] -= 1
        return not any(count < -3 or count > 3 for count in diff)