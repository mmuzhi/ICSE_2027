class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        if not forbidden:
            return len(word)
        
        trie = {}
        for f in forbidden:
            t = trie
            for c in f:
                if c not in t:
                    t[c] = {}
                t = t[c]
            t["end"] = True
        
        def isForbidden(s):
            t = trie
            n = len(s)
            for start in range(n):
                temp = trie
                for k in range(start, n):
                    c = s[k]
                    if c not in temp:
                        break
                    temp = temp[c]
                    if "end" in temp:
                        return True
                else:
                    continue
                break
            return False
        
        j = len(word)
        res = 0
        for i in range(len(word) - 1, -1, -1):
            if isForbidden(word[i:j]):
                j = i
            else:
                res = max(res, j - i)
        return res