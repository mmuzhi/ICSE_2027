class Solution:
    def numWays(self, s: str) -> int:
        MOD = 10**9 + 7
        n = len(s)
        ones = s.count('1')
        if ones == 0:
            return ((n-1)*(n-2)//2) % MOD
        if ones % 3 != 0:
            return 0
        target = ones // 3
        cnt = 0
        first_group_last = second_group_first = second_group_last = third_group_first = -1
        for i, ch in enumerate(s):
            if ch == '1':
                cnt += 1
                if cnt == target:
                    first_group_last = i
                if cnt == target + 1:
                    second_group_first = i
                if cnt == 2 * target:
                    second_group_last = i
                if cnt == 2 * target + 1:
                    third_group_first = i
        ways = (second_group_first - first_group_last) * (third_group_first - second_group_last)
        return ways % MOD