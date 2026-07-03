class Solution:
    def platesBetweenCandles(self, s: str, queries: List[List[int]]) -> List[int]:
        candies = [i for i, c in enumerate(s) if c == '|']
        
        if not candies:
            return [0] * len(queries)
        
        def bns(x: int) -> int:
            l, r = 0, len(candies) - 1
            while l <= r:
                m = (l + r) // 2
                if candies[m] < x:
                    l = m + 1
                else:
                    r = m - 1
            return l
        
        ans = []
        for a, b in queries:
            left_index = bns(a)
            right_index = bns(b + 1) - 1
            
            if left_index >= len(candies) or right_index < 0 or left_index > right_index:
                ans.append(0)
            else:
                ans.append(candies[right_index] - candies[left_index] - (right_index - left_index))
        
        return ans