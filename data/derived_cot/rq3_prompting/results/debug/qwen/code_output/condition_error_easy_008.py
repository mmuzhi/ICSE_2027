class Solution:
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        out = []
        for i in range(len(nums1)):
            try:
                pos = nums2.index(nums1[i])
            except ValueError:
                out.append(-1)
                continue
            if pos == len(nums2) - 1:
                out.append(-1)
            else:
                j = pos + 1
                while j < len(nums2):
                    if nums1[i] < nums2[j]:
                        out.append(nums2[j])
                        break
                    j += 1
                else:
                    out.append(-1)
        return out