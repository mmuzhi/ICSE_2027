class Solution:
    def minimumPartition(self, s: str, k: int) -> int:
        if s == "":
            return 0
        ans = 0
        curr = 0
        for d in s:
            if int(d) > k:
                return -1
            curr = curr * 10 + int(d)
            if curr > k:
                ans += 1
                curr = int(d)
        return ans + 1