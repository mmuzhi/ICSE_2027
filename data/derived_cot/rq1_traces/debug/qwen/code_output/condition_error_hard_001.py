class Solution:
    def palindromePairs(self, words: List[str]) -> List[List[int]]:
        d = {word: i for i, word in enumerate(words)}
        res = []
        n = len(words)
        for i, word in enumerate(words):
            n1 = len(word)
            for j in range(n1 + 1):
                # Case 1: Check if the suffix is a palindrome and the reverse of the prefix is in the dictionary.
                if j < n1 and word[j:] and word[j:][::-1] in d and word[:j] == word[:j][::-1]:
                    res.append([d[word[j:][::-1]], i])
                # Case 2: Check if the prefix is a palindrome and the reverse of the suffix is in the dictionary.
                if j < n1 and word[:j] and word[:j][::-1] in d and word[j:] == word[j:][::-1]:
                    res.append([i, d[word[:j][::-1]]])
        return res