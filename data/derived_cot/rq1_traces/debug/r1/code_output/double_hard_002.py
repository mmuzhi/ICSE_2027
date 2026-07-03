import collections
from typing import List

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not words:
            return []
        word_len = len(words[0])
        total_len = word_len * len(words)
        result = []
        word_count = collections.Counter(words)
        
        for i in range(word_len):
            if i + total_len > len(s):
                continue
            current_count = collections.defaultdict(int)
            # Initialize the sliding window
            for j in range(i, i + total_len, word_len):
                word = s[j:j+word_len]
                if word in word_count:
                    current_count[word] += 1
            if current_count == word_count:
                result.append(i)
            # Slide the window
            for j in range(i + word_len, len(s) - total_len + 1, word_len):
                # Remove the word leaving the window
                left_word = s[j - word_len:j]
                if left_word in word_count:
                    current_count[left_word] -= 1
                    if current_count[left_word] == 0:
                        del current_count[left_word]
                # Add the new word entering the window
                right_word = s[j + total_len - word_len:j + total_len]
                if right_word in word_count:
                    current_count[right_word] += 1
                if current_count == word_count:
                    result.append(j)
        return result