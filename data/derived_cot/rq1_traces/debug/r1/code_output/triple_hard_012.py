class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        trie = {}
        max_len_forbidden = 0
        for f in forbidden:
            max_len_forbidden = max(max_len_forbidden, len(f))
            node = trie
            for c in reversed(f):
                if c not in node:
                    node[c] = {}
                node = node[c]
            node['#'] = True  # Mark end of forbidden word
        
        left = 0
        max_length = 0
        for right in range(len(word)):
            current = trie
            for k in range(max_len_forbidden):
                start = right - k
                if start < 0:
                    break
                c = word[start]
                if c not in current:
                    break
                current = current[c]
                if '#' in current:
                    left = max(left, start + 1)
            max_length = max(max_length, right - left + 1)
        return max_length