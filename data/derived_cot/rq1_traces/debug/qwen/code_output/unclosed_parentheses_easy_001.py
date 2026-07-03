class Solution:
    def largestInteger(self, num: int) -> int:
        digits = [int(x) for x in str(num)]
        n = len(digits)
        even_digits = []
        odd_digits = []
        for d in digits:
            if d % 2 == 0:
                even_digits.append(d)
            else:
                odd_digits.append(d)
        even_digits.sort(reverse=True)
        odd_digits.sort(reverse=True)
        even_indices = (n + 1) // 2
        odd_indices = n // 2
        
        if len(even_digits) < even_indices or len(odd_digits) < odd_indices:
            return -1
        
        res = [''] * n
        even_index = 0
        odd_index = 0
        for i in range(n):
            if i % 2 == 0:
                res[i] = str(even_digits[even_index])
                even_index += 1
            else:
                res[i] = str(odd_digits[odd_index])
                odd_index += 1
        return int(''.join(res))