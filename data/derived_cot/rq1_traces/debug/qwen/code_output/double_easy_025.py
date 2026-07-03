class Solution:
    def canThreePartsEqualSum(self, arr: List[int]) -> bool:
        total = sum(arr)
        if total % 3 != 0:
            return False
        target = total // 3
        n = len(arr)
        if n < 3:
            return False
        
        prefix = [0] * n
        prefix[0] = arr[0]
        for i in range(1, n):
            prefix[i] = prefix[i-1] + arr[i]
        
        i_index = -1
        for i in range(n):
            if prefix[i] == target:
                i_index = i
                break
        
        if i_index == -1 or i_index >= n-1:
            return False
        
        for j in range(i_index+1, n-1):
            if prefix[j] == 2 * target:
                return True
        
        return False