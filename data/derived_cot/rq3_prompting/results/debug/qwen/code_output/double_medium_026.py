class Disjoint:
    def __init__(self):
        self.rank = [0] * 62
        self.parent = [i for i in range(62)]
    
    def finduPar(self, node):
        if self.parent[node] == node:
            return node
        self.parent[node] = self.finduPar(self.parent[node])
        return self.parent[node]
    
    def byrank(self, u, v):
        ulp_u = self.finduPar(u)
        ulp_v = self.finduPar(v)
        if ulp_u == ulp_v:
            return
        if self.rank[ulp_u] > self.rank[ulp_v]:
            self.parent[ulp_v] = ulp_u
        elif self.rank[ulp_u] < self.rank[ulp_v]:
            self.parent[ulp_u] = ulp_v
        else:
            self.parent[ulp_v] = ulp_u
            self.rank[ulp_u] += 1

class Solution:
    def equationsPossible(self, equations: List[str]) -> bool:
        disjoint = Disjoint()
        nq = []
        for eq in equations:
            if eq[1] == '!':
                if eq[0] == eq[-1]:
                    return False
                else:
                    nq.append(eq)
            else:
                x = ord(eq[0]) - 48 if eq[0] in '0123456789' else ord(eq[0]) - 97
                y = ord(eq[-1]) - 48 if eq[-1] in '0123456789' else ord(eq[-1]) - 97
                if x == y:
                    continue
                disjoint.byrank(x, y)
        for eq in nq:
            x = ord(eq[0]) - 48 if eq[0] in '0123456789' else ord(eq[0]) - 97
            y = ord(eq[-1]) - 48 if eq[-1] in '0123456789' else ord(eq[-1]) - 97
            if disjoint.finduPar(x) == disjoint.finduPar(y):
                return False
        return True