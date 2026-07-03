from typing import List
import collections

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not s or not words:
            return []
        wlen = len(words[0])
        total_len = wlen * len(words)
        word_count = collections.Counter(words)
        res = []

        for offset in range(wlen):
            left = offset
            track = collections.Counter()
            for right in range(offset, len(s) - wlen + 1, wlen):
                word = s[right:right + wlen]
                if word in word_count:
                    track[word] += 1
                    # shrink window if too many occurrences of a word
                    while track[word] > word_count[word]:
                        left_word = s[left:left + wlen]
                        track[left_word] -= 1
                        left += wlen
                    # check if window matches the required length
                    if right - left + wlen == total_len:
                        res.append(left)
                        # slide the window by one word
                        left_word = s[left:left + wlen]
                        track[left_word] -= 1
                        left += wlen
                else:
                    # reset window if word not in list
                    track.clear()
                    left = right + wlen
        return res