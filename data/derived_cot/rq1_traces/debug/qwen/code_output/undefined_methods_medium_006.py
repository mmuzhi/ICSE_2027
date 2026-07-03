class Solution:
    def powerfulIntegers(self, x: int, y: int, bound: int):
        if bound == 0:
            return []
        
        def get(v):
            yield 1
            if v == 1:
                return
            vi = v
            while vi <= bound:
                yield vi
                vi *= v
        
        res = set()
        for xi in get(x):
            for yi in get(y):
                s = xi + yi
                if s <= bound:
                    res.add(s)
        return list(res)