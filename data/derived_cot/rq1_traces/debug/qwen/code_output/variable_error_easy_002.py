class Solution:
    def findRestaurant(self, list1: List[str], list2: List[str]) -> List[str]:
        d2 = {}
        for i, restaurant in enumerate(list2):
            if restaurant not in d2:
                d2[restaurant] = i
        
        common = []
        for i, restaurant in enumerate(list1):
            if restaurant in d2:
                common.append([i + d2[restaurant], restaurant])
                
        if not common:
            return []
        
        common.sort(key=lambda x: x[0])
        min_index = common[0][0]
        result = []
        for item in common:
            if item[0] == min_index:
                result.append(item[1])
            else:
                break
                
        return result