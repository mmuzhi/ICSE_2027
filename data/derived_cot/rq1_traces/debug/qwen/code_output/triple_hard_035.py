class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not s2 or not s1:
            return 0
        if not set(s2).issubset(set(s1)):
            return 0
        
        j = 0
        count = 0
        i = 0
        visited = {}
        total_chars = n1 * len(s1)
        
        for copy in range(n1):
            while i < len(s1):
                if j < len(s2) and s1[i] == s2[j]:
                    j += 1
                    if j == len(s2):
                        count += 1
                        j = 0
                state = (j, i)
                if state in visited:
                    prev_count, prev_total = visited[state]
                    cycle_length = (copy * len(s1) + i) - prev_total
                    cycle_count = count - prev_count
                    remaining_chars = total_chars - (copy * len(s1) + i)
                    complete_cycles = remaining_chars // cycle_length
                    count += complete_cycles * cycle_count
                    break
                visited[state] = (count, copy * len(s1) + i)
                i += 1
            else:
                continue
            break
        
        return count // n2