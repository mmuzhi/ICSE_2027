class Solution:
    def canThreePartsEqualSum(self, arr: List[int]) -> bool:
        total = sum(arr)
        if total % 3 != 0:
            return False
        each_sum = total // 3
        if len(arr) < 3:
            return False
        sumi = 0
        count = 0
        for x in arr:
            sumi += x
            if sumi == each_sum:
                sumi = 0
                count += 1
                if count == 3:
                    return True
        return count == 3