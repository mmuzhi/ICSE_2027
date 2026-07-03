import collections
from typing import List

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if not words:
            return []
        word_length = len(words[0])
        total_words = len(words)
        substring_length = word_length * total_words
        word_count = collections.Counter(words)
        result = []
        
        def is_valid():
            for word, count in word_count.items():
                if current_counts.get(word, 0) != count:
                    return False
            return True
        
        for start_offset in range(word_length):
            current_counts = {word: 0 for word in word_count}
            # Initialize the current window
            for i in range(start_offset, start_offset + substring_length, word_length):
                if i + word_length > len(s):
                    break
                current_word = s[i:i + word_length]
                if current_word in word_count:
                    current_counts[current_word] += 1
            if is_valid():
                result.append(start_offset)
            # Slide the window
            for new_start in range(start_offset + word_length, len(s) - substring_length + 1, word_length):
                # Remove the outgoing word
                outgoing_word = s[new_start - word_length:new_start]
                if outgoing_word in word_count:
                    current_counts[outgoing_word] -= 1
                # Add the incoming word
                incoming_word = s[new_start + substring_length - word_length:new_start + substring_length]
                if incoming_word in word_count:
                    current_counts[incoming_word] += 1
                if is_valid():
                    result.append(new_start)
        
        return result