class Solution:
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        l = []
        for i in nums1:
            count = 0
            idx = nums2.index(i)
            for k in range(idx + 1, len(nums2)):
                if nums2[k] > i:
                    count += 1
                    l.append(nums2[k])
                    break
            if count == 0:
                l.append(-1)
        return l