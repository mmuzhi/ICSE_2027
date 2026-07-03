class Solution:
    def canThreePartsEqualSum(self, arr: List[int]) -> bool:
        total = sum(arr)
        if total % 3 != 0:
            return False
        each_sum = total // 3
        if len(arr) < 3:
            return False
        
        count = 0
        current_sum = 0
        for i in range(len(arr)-1):
            current_sum += arr[i]
            if current_sum == each_sum:
                count += 1
                current_sum = 0
            if count == 2:
                return True
        return False