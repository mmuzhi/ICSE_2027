class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0

        if s2 == "":
            return 0

        next_pos = {}
        for c in set(s2):
            next_pos[c] = []
        
        for i, c in enumerate(s1):
            if c in next_pos:
                next_pos[c].append(i)
        
        seen = {}
        count = 0
        total_chars = 0
        start = 0
        
        while start < len(s2) and total_chars < len(s1) * n1:
            c = s2[start]
            if c not in next_pos:
                return count // n2
            
            copy_index = total_chars // len(s1)
            remaining = total_chars % len(s1)
            
            if copy_index >= n1:
                return count // n2
            
            arr = next_pos[c]
            idx = bisect.bisect_left(arr, remaining)
            if idx >= len(arr):
                total_chars = (copy_index + 1) * len(s1)
                start = 0
                if start not in seen:
                    seen[start] = (total_chars, count)
                continue
            else:
                total_chars = arr[idx] + 1
                start += 1
                if start == len(s2):
                    count += 1
                    start = 0
                    if start not in seen:
                        seen[start] = (total_chars, count)
        
        return count // n2