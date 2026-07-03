class Solution:
    def findRestaurant(self, list1: List[str], list2: List[str]) -> List[str]:
        d2 = {}
        for i in range(len(list2)):
            d2[list2[i]] = i
        
        l = []
        for i in range(len(list1)):
            if list1[i] in d2:
                l.append([i + d2[list1[i]], list1[i]])
        
        if not l:
            return []
        
        l.sort()
        result = [item[1] for item in l if item[0] == l[0][0]]
        return result