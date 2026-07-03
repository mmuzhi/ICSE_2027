class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        trie = {}
        max_len = 0
        for f in forbidden:
            flen = len(f)
            if flen > max_len:
                max_len = flen
            node = trie
            for c in f:
                if c not in node:
                    node[c] = {}
                node = node[c]
            node['#'] = True  # Mark end of forbidden word
        
        n = len(word)
        res = 0
        right = n
        for left in range(n-1, -1, -1):
            current = trie
            for i in range(left, min(left + max_len, right)):
                c = word[i]
                if c not in current:
                    break
                current = current[c]
                if '#' in current:
                    right = i + 1
                    break
            res = max(res, right - left)
        return res