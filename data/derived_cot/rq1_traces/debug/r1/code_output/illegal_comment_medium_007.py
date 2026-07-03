class Solution:
    def minimumPartition(self, s: str, k: int) -> int:
        ans = 1
        curr = 0
        for d in s:
            d_int = int(d)
            if d_int > k:
                return -1
            if curr * 10 + d_int > k:
                ans += 1
                curr = d_int
            else:
                curr = curr * 10 + d_int
        return ans