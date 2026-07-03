class Solution:
    def canThreePartsEqualSum(self, arr: List[int]) -> bool:
        total = sum(arr)
        if total % 3 != 0:
            return False
        each_sum = total // 3
        count = 0
        current = 0
        for num in arr:
            current += num
            if current == each_sum:
                count += 1
                current = 0
            if count == 3:
                return True
        return False