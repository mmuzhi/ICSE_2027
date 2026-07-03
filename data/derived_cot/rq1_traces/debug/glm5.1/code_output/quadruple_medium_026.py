from typing import List
from collections import defaultdict, deque

class Solution:
    def findAllRecipes(self, recepies: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        dct = defaultdict(list)
        indegree = {}
        n = len(recepies)
        supplies_set = set(supplies)
        recepies_set = set(recepies)

        for i in recepies:
            indegree[i] = 0

        for i in range(n):
            for j in ingredients[i]:
                indegree[j] = 0

        for i in range(n):
            for j in ingredients[i]:
                dct[j].append(recepies[i])
                indegree[recepies[i]] += 1

        st = deque()
        for i in indegree:
            if indegree[i] == 0:
                if i in supplies_set or i in recepies_set:
                    st.append(i)
        
        flst = []
        while st:
            x = st.popleft()
            for i in dct[x]:
                indegree[i] -= 1
                if indegree[i] == 0:
                    st.append(i)
            if x in recepies_set:
                flst.append(x)

        return flst