from collections import defaultdict, deque

class Solution:
    def findAllRecipes(self, recepies: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        dct = defaultdict(list)
        indegree = defaultdict(int)
        n = len(recepies)
        recipe_set = set(recepies)

        for i in range(n):
            for j in ingredients[i]:
                dct[j].append(recepies[i])
                indegree[recepies[i]] += 1

        st = deque(supplies)
        flst = []
        while st:
            x = st.popleft()
            for i in dct[x]:
                indegree[i] -= 1
                if indegree[i] == 0:
                    st.append(i)
                    if i in recipe_set:
                        flst.append(i)

        return flst