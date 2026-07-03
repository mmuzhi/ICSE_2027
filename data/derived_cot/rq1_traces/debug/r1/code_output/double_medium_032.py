class Solution:
    def platesBetweenCandles(self, s: str, queries: List[List[int]]) -> List[int]:
        candies = [i for i, c in enumerate(s) if c == '|']
        
        def bns(x: int) -> int:
            l, r = 0, len(candies)
            while l < r:
                m = (l + r) // 2
                if candies[m] < x:
                    l = m + 1
                else:
                    r = m
            return l

        ans = []
        for a, b in queries:
            l_index = bns(a)
            r_index = bns(b + 1) - 1
            if l_index <= r_index and l_index < len(candies) and r_index >= 0:
                plates = candies[r_index] - candies[l_index] - (r_index - l_index)
                ans.append(plates)
            else:
                ans.append(0)
        return ans