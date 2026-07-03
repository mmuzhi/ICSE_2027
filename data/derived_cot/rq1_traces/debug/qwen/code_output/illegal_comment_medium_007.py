class Solution:
    def minimumPartition(self, s: str, k: int) -> int:
        n = len(s)
        ans = 0
        i = 0
        while i < n:
            if int(s[i]) > k:
                return -1
            j = i
            curr = 0
            while j < n:
                digit_val = int(s[j])
                curr = curr * 10 + digit_val
                if curr > k:
                    break
                j += 1
            ans += 1
            i = j
        return ans