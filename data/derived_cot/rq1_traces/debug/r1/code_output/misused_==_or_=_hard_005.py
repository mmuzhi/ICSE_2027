from collections import Counter, defaultdict
from typing import List

class Solution:
    def minimumTotalCost(self, nums1: List[int], nums2: List[int]) -> int:
        n = len(nums1)
        count1 = Counter(nums1)
        count2 = Counter(nums2)
        
        # Check if any element in nums1 and nums2 makes it impossible
        for num in count1:
            if (n - count2[num]) < count1[num]:
                return -1
            if count1[num] > n // 2 and count2[num] > n // 2:
                return -1
        for num in count2:
            if (n - count1[num]) < count2[num]:
                return -1
            if count1[num] > n // 2 and count2[num] > n // 2:
                return -1
        
        # Collect indices where nums1[i] == nums2[i]
        equal_counts = Counter()
        ans = 0
        vis = [0] * n
        d = defaultdict(list)
        
        for i in range(n):
            if nums1[i] == nums2[i]:
                equal_counts[nums2[i]] += 1
                ans += i
                d[nums2[i]].append(i)
        
        # If no equal elements, cost is 0
        if not equal_counts:
            return 0
        
        # Process the most common element in equal positions
        most_common = equal_counts.most_common()
        main_num, main_count = most_common[0]
        other_total = sum(count for _, count in most_common[1:])
        
        if other_total >= main_count:
            return ans
        
        # Need additional swaps
        required = main_count - other_total
        for num in most_common[1:]:
            for idx in d[num[0]]:
                vis[idx] = 1
        
        # Find additional indices to swap
        additional = 0
        for i in range(n):
            if not vis[i] and nums1[i] != main_num and nums2[i] != main_num:
                ans += i
                additional += 1
                if additional == required:
                    break
        
        return ans if additional >= required else -1