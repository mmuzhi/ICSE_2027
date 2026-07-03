class Solution:
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        l = []
        for i in nums1:
            found_index = None
            for idx, j in enumerate(nums2):
                if j == i:
                    found_index = idx
                    break
            if found_index is None:
                l.append(-1)
            else:
                found = False
                for k in range(found_index + 1, len(nums2)):
                    if nums2[k] > i:
                        l.append(nums2[k])
                        found = True
                        break
                if not found:
                    l.append(-1)
        return l