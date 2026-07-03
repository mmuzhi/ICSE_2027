class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not s2:
            return n2
        
        if not set(s2).issubset(set(s1)):
            return 0
        
        len_s1 = len(s1)
        len_s2 = len(s2)
        
        state = 0
        total_chars = 0
        count = 0
        
        while total_chars < n1 * len_s1:
            if state == len_s2:
                count += 1
                state = 0
            
            if state >= len_s2:
                continue
                
            char = s2[state]
            current_copy = total_chars // len_s1
            current_pos = total_chars % len_s1
            
            pos_in_s1 = s1.find(char, current_pos)
            if pos_in_s1 == -1:
                total_chars = (current_copy + 1) * len_s1
                if total_chars >= n1 * len_s1:
                    break
                current_pos = 0
            else:
                total_chars = current_copy * len_s1 + pos_in_s1 + 1
                state += 1
        
        return count