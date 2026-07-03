from typing import List
from math import ceil

class Solution:
    def minSpeedOnTime(self, dist: List[int], hour: float) -> int:
        if len(dist) - 1 >= hour: return -1
        left,right = 1, ceil(max(max(dist),dist[-1]/(1 if hour.is_integer() else hour-int(hour))))
        while left<right:
            mid=(left+right)//2
            if sum([ceil(i/mid) for i in dist[:-1]])+(dist[-1]/mid) <= hour :
                right=mid
            else:
                left=mid+1
        return left