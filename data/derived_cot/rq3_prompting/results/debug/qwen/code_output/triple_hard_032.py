class Solution:
    def findKthNumber(self, n: int, k: int) -> int:
        def fn(x):
            if x == 0:
                return 0
            s = str(x)
            d = len(s)
            low = 10**(d-1)
            high = min(n, 10**d - 1)
            if x < low:
                x = low
            if x > high:
                return 0
            
            def is_valid(num):
                s_num = str(num)
                for i in range(1, len(s_num)):
                    if s_num[i] < s_num[i-1]:
                        return False
                return True
            
            count = 0
            for num in range(x, high + 1):
                if is_valid(num):
                    count += 1
                    if count == k:
                        return num
            return x
        
        x = 1
        while k > 1:
            cnt = fn(x)
            if k > cnt:
                k -= cnt
                x += 1
            else:
                k -= 1
                x += 1
        return x