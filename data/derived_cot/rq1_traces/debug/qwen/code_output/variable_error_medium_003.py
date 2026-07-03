from typing import List

class Solution:
    def getFolderNames(self, names: List[str]) -> List[str]:
        ans = []
        used = set()
        
        for name in names:
            if name not in used:
                ans.append(name)
                used.add(name)
            else:
                k = 1
                while True:
                    new_name = name + '(' + str(k) + ')'
                    if new_name not in used:
                        ans.append(new_name)
                        used.add(new_name)
                        break
                    k += 1
        
        return ans