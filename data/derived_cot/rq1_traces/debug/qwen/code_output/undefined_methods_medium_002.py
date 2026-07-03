class Solution:
    def fourSumCount(self, nums1: List[int], nums2: List[int], nums3: List[int], nums4: List[int]) -> int:
        dictionary = {}
        for n1 in nums1:
            for n2 in nums2:
                s = n1 + n2
                dictionary[s] = dictionary.get(s, 0) + 1
        
        numberOfTuples = 0
        for n3 in nums3:
            for n4 in nums4:
                s = n3 + n4
                numberOfTuples += dictionary.get(-s, 0)
        
        return numberOfTuples