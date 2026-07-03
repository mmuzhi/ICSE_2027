from collections import Counter, defaultdict

class Solution:
    def minimumTotalCost(self, nums1: List[int], nums2: List[int]) -> int:
        n = len(nums1)
        z = Counter(nums1)
        z1 = Counter(nums2)
        for i in z:
            if n - z1[i] < z[i]:
                return -1
            if z[i] >= n//2 + 1 and z1[i] >= n//2 + 1:
                return -1
        for i in z1:
            if n - z[i] < z1[i]:
                return -1
            if z[i] >= n//2 + 1 and z1[i] >= n//2 + 1:
                return -1
        z = Counter()
        ans = 0
        d = defaultdict(list)
        vis = [0] * n
        for i in range(n):
            if nums1[i] == nums2[i]:
                d[nums1[i]].append(i)
                ans += i
        if not d:
            return 0
        l = []
        for num, count in d.items():
            l.append((count, num))
        l.sort(reverse=True)
        a = 0
        for i in range(1, len(l)):
            a += l[i][0]
            for idx in l[i][1]:
                vis[idx] = 1
        if l and a >= l[0][0]:
            return ans
        x = l[0][0] - a if l else 0
        for num, count in d.items():
            if count > a:
                for idx in range(n):
                    if not vis[idx] and nums1[idx] != num and nums2[idx] != num and x:
                        ans += idx
                        x -= 1
        return ans