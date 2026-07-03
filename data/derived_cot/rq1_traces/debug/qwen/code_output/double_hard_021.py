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
            for start in range(n):
                t = trie
                for pos in range(start, n):
                    c = s[pos]
                    if c not in t:
                        break
                    t = t[c]
                    if "end" in t:
                        return start
                else:
                    continue
                break
            return False
        
        res = 0
        j = len(word)
        for i in range(len(word) - 1, -1, -1):
            start_index = isForbidden(word[i:j])
            if start_index is not False:
                j = start_index + 1
            res = max(res, j - i)
        return res