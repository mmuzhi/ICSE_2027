from typing import List

class Solution:
    def deckRevealedIncreasing(self, deck: List[int]) -> List[int]:
        def reveal(n):
            lst = list(range(n))
            ans = []
            i = 0
            while lst:
                if not i % 2:
                    ans.append(lst.pop(0))
                else:
                    lst.append(lst.pop(0))
                i += 1
            return ans
        
        order = reveal(len(deck))
        mapped = sorted([(pos, idx) for idx, pos in enumerate(order)], key=lambda x: x[0])
        deck.sort()
        return [deck[idx] for _, idx in mapped]