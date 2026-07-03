class Solution:
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        out = []
        for num in nums1:
            idx = nums2.index(num)
            if idx == len(nums2) - 1:
                out.append(-1)
            else:
                j = idx + 1
                while True:
                    if j == len(nums2):
                        out.append(-1)
                        break
                    if nums2[j] > num:
                        out.append(nums2[j])
                        break
                    j += 1
        return out