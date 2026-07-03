class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        if not word or not forbidden:
            return 0
        
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
                node = trie
                for pos in range(start, n):
                    c = s[pos]
                    if c not in node:
                        break
                    node = node[c]
                    if "end" in node:
                        return True
                else:
                    continue
                break
            return False
        
        n = len(word)
        j = 0
        max_length = 0
        for i in range(n):
            while j < n and not isForbidden(word[i:j]):
                j += 1
            if j > i:
                valid_length = j - i - 1
                max_length = max(max_length, valid_length)
        return max_length