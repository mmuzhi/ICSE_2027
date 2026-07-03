from collections import Counter, defaultdict

class Solution:
    def minimumTotalCost(self, nums1: List[int], nums2: List[int]) -> int:
        n = len(nums1)
        z = Counter(nums1)
        z1 = Counter(nums2)
        
        for i in z:
            if z[i] > n - z1.get(i, 0):
                return -1
        
        for i in z1:
            if z1[i] > n - z.get(i, 0):
                return -1
        
        vis = [0] * n
        ans = 0
        d = defaultdict(list)
        for i in range(n):
            if nums1[i] == nums2[i]:
                d[nums1[i]].append(i)
                ans += i
                vis[i] = 1
        
        if not z:
            return ans
        
        top_num, top_freq = z.most_common(1)[0]
        other_sum = 0
        for num, count in z.items():
            if num == top_num:
                continue
            other_sum += count
        
        if top_freq >= other_sum:
            return ans
        
        x = top_freq - other_sum
        for i in range(n):
            if vis[i] == 0 and (nums1[i] == top_num or nums2[i] == top_num):
                ans += i
                x -= 1
                if x == 0:
                    break
        
        return ans