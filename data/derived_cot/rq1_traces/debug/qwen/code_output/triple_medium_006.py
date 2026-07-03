class Solution:
    def stoneGameVI(self, a: List[int], b: List[int]) -> int:
        n = len(a)
        piles = []
        for i in range(n):
            piles.append((a[i] + b[i], a[i], b[i]))
        piles.sort(key=lambda x: x[0], reverse=True)
        
        alice_total = 0
        bob_total = 0
        for idx, (total, a_val, b_val) in enumerate(piles):
            if idx % 2 == 0:
                alice_total += a_val
            else:
                bob_total += b_val
                
        if alice_total > bob_total:
            return 1
        elif alice_total < bob_total:
            return -1
        else:
            return 0