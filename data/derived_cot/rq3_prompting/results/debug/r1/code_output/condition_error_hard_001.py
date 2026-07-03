from typing import List

class Solution:
    def palindromePairs(self, words: List[str]) -> List[List[int]]:
        backward = {}
        for i, word in enumerate(words):
            backward[word[::-1]] = i

        res = []
        for i, word in enumerate(words):
            # Exact reverse exists (but not itself)
            if word in backward and backward[word] != i:
                res.append([i, backward[word]])

            # Empty string handling
            if word != "" and "" in backward and word == word[::-1]:
                res.append([i, backward[""]])
                res.append([backward[""], i])

            # Check splits (exclude empty prefix/suffix to avoid duplicates)
            for j in range(1, len(word)):
                # Suffix exists as reversed word and prefix is palindrome
                if word[j:] in backward and word[:j] == word[:j][::-1]:
                    if backward[word[j:]] != i:
                        res.append([backward[word[j:]], i])
                # Prefix exists as reversed word and suffix is palindrome
                if word[:j] in backward and word[j:] == word[j:][::-1]:
                    if backward[word[:j]] != i:
                        res.append([i, backward[word[:j]]])

        return res