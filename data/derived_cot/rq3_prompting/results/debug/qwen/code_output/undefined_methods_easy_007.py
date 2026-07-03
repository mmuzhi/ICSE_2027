class Solution:
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        l = []
        for i in nums1:
            pos = nums2.index(i)
            for k in range(pos+1, len(nums2)):
                if nums2[k] > i:
                    l.append(nums2[k])
                    break
            else:
                l.append(-1)
        return l