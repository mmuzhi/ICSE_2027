from typing import List

class Solution:
    def findRestaurant(self, list1: List[str], list2: List[str]) -> List[str]:
        d2 = {}
        l = []
        for i in range(len(list2)):
            d2[list2[i]] = i
        for i in range(len(list1)):
            if list1[i] in d2:
                l.append([i + d2[list1[i]], list1[i]])
        l.sort()
        if not l:
            return []
        min_sum = l[0][0]
        l1 = []
        for x in l:
            if x[0] == min_sum:
                l1.append(x[1])
            else:
                break
        return l1