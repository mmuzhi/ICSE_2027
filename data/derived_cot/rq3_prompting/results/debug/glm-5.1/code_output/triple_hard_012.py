class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        trie = {}
        for f in forbidden:
            t = trie
            for c in f:
                if c not in t:
                    t[c] = {}
                t = t[c]
            t["end"] = True
        
        res = 0
        j = len(word)
        for i in range(len(word) - 1, -1, -1):
            t = trie
            for k in range(i, min(j, i + 10)):
                if word[k] not in t:
                    break
                t = t[word[k]]
                if "end" in t:
                    j = k
                    break
            res = max(res, j - i)
        return res