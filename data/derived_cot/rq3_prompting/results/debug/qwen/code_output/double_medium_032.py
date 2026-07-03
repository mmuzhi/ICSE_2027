class Solution:
    def platesBetweenCandles(self, s: str, queries: List[List[int]]) -> List[int]:
        candies = [i for i, c in enumerate(s) if c == '|']
        n = len(candies)
        
        def bns(x: int) -> int:
            l, r = 0, n
            while l < r:
                m = (l + r) // 2
                if candies[m] < x:
                    l = m + 1
                else:
                    r = m
            return l
        
        ans = []
        for a, b in queries:
            left_index = bns(a)
            right_index = bns(b + 1) - 1
            if left_index < right_index:
                ans.append(candies[right_index] - candies[left_index] - (right_index - left_index))
            else:
                ans.append(0)
        return ans