class Solution:
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        result = []
        for num in nums1:
            index_in_nums2 = nums2.index(num)
            next_greater = -1
            for k in range(index_in_nums2 + 1, len(nums2)):
                if nums2[k] > num:
                    next_greater = nums2[k]
                    break
            result.append(next_greater)
        return result