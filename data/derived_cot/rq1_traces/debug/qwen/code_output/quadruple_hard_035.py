import bisect
from collections import defaultdict

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not s2:
            return 0
        
        if not set(s2).issubset(set(s1)):
            return 0
        
        s1_filtered = ''.join(char for char in s1 if char in set(s2))
        if not s1_filtered:
            return 0
        
        L = len(s1_filtered)
        total_length = n1 * L
        
        positions = {}
        for char in set(s2):
            positions[char] = [i for i, c in enumerate(s1_filtered) if c == char]
        
        j = 0
        count = 0
        current_position = 0
        
        while current_position < total_length:
            if j < len(s2):
                c = s2[j]
                if c not in positions:
                    break
                arr = positions[c]
                copy_index = current_position // L
                index_in_copy = current_position % L
                
                if copy_index >= n1:
                    break
                
                idx = bisect.bisect_left(arr, index_in_copy)
                if idx < len(arr):
                    next_pos = copy_index * L + arr[idx]
                    current_position = next_pos + 1
                    j += 1
                else:
                    if copy_index == n1 - 1:
                        break
                    next_pos = (copy_index + 1) * L + arr[0]
                    current_position = next_pos + 1
                    j += 1
            else:
                count += 1
                j = 0
        
        return count