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
        
        def isForbidden(s):
            n = len(s)
            if n == 0:
                return False
            for start in range(n):
                temp = trie
                for pos in range(start, n):
                    c = s[pos]
                    if c not in temp:
                        break
                    temp = temp[c]
                    if "end" in temp:
                        return True
            return False
        
        res = 0
        j = len(word)
        for i in range(len(word) - 1, -1, -1):
            if isForbidden(word[i:j]):
                j = i + (isForbidden(word[i:j]) - 1)
            else:
                res = max(res, j - i)
        return res