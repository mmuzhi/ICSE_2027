from typing import List
import collections

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not s or not words:
            return []
        wlen = len(words[0])
        num_words = len(words)
        total_len = wlen * num_words
        word_count = collections.Counter(words)
        res = []

        for offset in range(wlen):
            left = offset
            right = offset
            curr_count = collections.Counter()
            while right + wlen <= len(s):
                word = s[right:right+wlen]
                right += wlen
                if word in word_count:
                    curr_count[word] += 1
                    while curr_count[word] > word_count[word]:
                        left_word = s[left:left+wlen]
                        curr_count[left_word] -= 1
                        left += wlen
                    if right - left == total_len:
                        res.append(left)
                else:
                    curr_count.clear()
                    left = right
        return res