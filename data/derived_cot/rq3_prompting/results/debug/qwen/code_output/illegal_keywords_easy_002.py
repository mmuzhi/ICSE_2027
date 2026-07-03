class Solution:
    def findRestaurant(self, list1: List[str], list2: List[str]) -> List[str]:
        d2 = {}
        for i, s in enumerate(list2):
            if s not in d2:
                d2[s] = i
        l = []
        for i in range(len(list1)):
            if list1[i] in d2:
                l.append([i + d2[list1[i]], list1[i]])
        if not l:
            return []
        l.sort()
        l1 = []
        l1.append(l[0][1])
        for i in range(1, len(l)):
            if l[i][0] == l[i-1][0]:
                l1.append(l[i][1])
            else:
                break
        return l1