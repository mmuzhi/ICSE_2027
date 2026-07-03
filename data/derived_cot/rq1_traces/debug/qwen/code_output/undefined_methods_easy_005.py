class Solution:
    def canThreePartsEqualSum(self, arr: List[int]) -> bool:
        total = sum(arr)
        if total % 3 != 0:
            return False
        each_sum = total // 3
        count = 0
        current_sum = 0
        for i in range(len(arr)):
            current_sum += arr[i]
            if current_sum == each_sum:
                current_sum = 0
                count += 1
                if count == 2:
                    if i + 1 < len(arr):
                        return True
                    else:
                        return False
        return False