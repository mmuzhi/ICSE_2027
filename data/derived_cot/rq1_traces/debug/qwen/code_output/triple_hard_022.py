class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not s2:
            return 0
        
        if not set(s2).issubset(set(s1)):
            return 0
        
        current_position = 0
        total_s1_used = 0
        rec = [0]
        visited = {}
        
        while True:
            completed = False
            for char in s2:
                pos = s1.find(char, current_position)
                if pos == -1:
                    total_s1_used += 1
                    pos = s1.find(char)
                    if pos == -1:
                        return 0
                    current_position = pos + 1
                else:
                    current_position = pos + 1
                
                if char == s2[-1]:
                    completed = True
                    rec.append(total_s1_used)
                    if current_position not in visited:
                        visited[current_position] = total_s1_used
                    else:
                        cycle_start = visited[current_position]
                        cycle_length = total_s1_used - cycle_start
                        cycle_occurrences = len(rec) - rec.index(cycle_start) - 1
                        break
            
            if not completed:
                break
            
            if 'cycle_start' in locals():
                break
        
        if not rec[-1] >= n1:
            return (len(rec) - 1) // n2
        
        cycle_start = visited[current_position]
        cycle_length = total_s1_used - cycle_start
        cycle_occurrences = len(rec) - rec.index(cycle_start) - 1
        remaining = n1 - cycle_start
        
        full_cycles = remaining // cycle_length
        extra_occurrences = 0
        temp = cycle_start
        while temp <= remaining:
            for char in s2:
                pos = s1.find(char, temp)
                if pos == -1:
                    temp += 1
                    pos = s1.find(char)
                    if pos == -1:
                        break
                temp = pos + 1
                if char == s2[-1]:
                    extra_occurrences += 1
                    break
        
        total_occurrences = cycle_occurrences * full_cycles + extra_occurrences
        return total_occurrences // n2