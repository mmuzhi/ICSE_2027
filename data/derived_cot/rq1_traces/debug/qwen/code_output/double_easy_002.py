import heapq

class Solution:
    def largestInteger(self, num: int) -> int:
        nums = [int(x) for x in str(num)]
        even_list = [d for d in nums if d % 2 == 0]
        odd_list = [d for d in nums if d % 2 != 0]
        
        even = [-x for x in even_list]
        odd = [-x for x in odd_list]
        heapq.heapify(even)
        heapq.heapify(odd)
        
        result = []
        total_digits = len(even_list) + len(odd_list)
        
        for _ in range(total_digits):
            if not even and not odd:
                break
            if not even:
                result.append(-heapq.heappop(odd))
            elif not odd:
                result.append(-heapq.heappop(even))
            else:
                if -even[0] > -odd[0]:
                    result.append(-heapq.heappop(even))
                else:
                    result.append(-heapq.heappop(odd))
        
        return int(''.join(str(x) for x in result))