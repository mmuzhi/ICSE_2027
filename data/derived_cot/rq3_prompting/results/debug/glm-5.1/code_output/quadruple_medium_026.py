from collections import defaultdict, deque
from typing import List

class Solution:
    def findAllRecipes(self, recepies: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        dct=defaultdict(lambda :[])
        indegree={}
        n=len(recepies)
        recepies_set=set(recepies)
        supplies_set=set(supplies)

        for i in recepies:
            indegree[i]=0

        for i in range(n):
            for j in ingredients[i]:
                indegree[j]=0

        for i in range(n):
            for j in ingredients[i]:
                dct[j].append(recepies[i])
                indegree[recepies[i]]+=1

        st=deque()
        for i in indegree:
            if indegree[i]==0:
                st.append(i)
                
        flst=[]
        ans=defaultdict(lambda :[])
        while st:
            x=st.popleft()
            for i in dct[x]:
                for j in ans[x]:
                    if j not in ans[i]:
                        ans[i].append(j)
                if x not in ans[i]:
                    ans[i].append(x)
                indegree[i]-=1
                if indegree[i]==0:
                    st.append(i)
            if x in recepies_set:
                for k in ans[x]:
                    if k not in supplies_set:
                        break
                else:
                    flst.append(x)
                    supplies_set.add(x)

        return flst