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
            for start in range(len(s)):
                node = trie
                for c in s[start:]:
                    if c not in node:
                        break
                    node = node[c]
                    if "end" in node:
                        return start + 1
            return 0
        
        res = 0
        j = len(word) + 1
        for i in range(len(word) - 1, -1, -1):
            truc = isForbidden(word[i:j])
            if truc:
                j = i + truc - 1
            res = max(res, j - i)
        return res