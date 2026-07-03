class Solution:
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        out = []
        for x in nums1:
            try:
                idx = nums2.index(x)
            except ValueError:
                out.append(-1)
                continue
            found = False
            for j in range(idx + 1, len(nums2)):
                if nums2[j] > x:
                    out.append(nums2[j])
                    found = True
                    break
            if not found:
                out.append(-1)
        return out