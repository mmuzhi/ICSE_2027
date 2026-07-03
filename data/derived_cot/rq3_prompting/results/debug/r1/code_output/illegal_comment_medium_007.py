class Solution:
    def minimumPartition(self, s: str, k: int) -> int:
        curr = 0
        ans = 0
        for d in s:
            digit = int(d)
            if digit > k:
                return -1
            curr = curr * 10 + digit
            if curr > k:
                ans += 1
                curr = digit
        return ans + 1