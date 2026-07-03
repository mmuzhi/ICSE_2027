from collections import deque

class Solution:
    def deckRevealedIncreasing(self, deck: List[int]) -> List[int]:
        def reveal(n):
            lst = deque(range(n))
            ans = []
            i = 0
            while lst:
                if not i & 1:
                    ans.append(lst.popleft())
                else:
                    x = lst.popleft()
                    lst.append(x)
                i += 1
            return ans
        
        indices = reveal(len(deck))
        deck.sort()
        return [deck[i] for i in indices]