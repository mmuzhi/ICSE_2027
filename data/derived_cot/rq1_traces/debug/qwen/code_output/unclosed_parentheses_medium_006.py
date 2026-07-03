class Solution:
    def deckRevealedIncreasing(self, deck: List[int]) -> List[int]:
        def reveal(n):
            lst = list(range(n))
            ans = []
            i = 0
            while lst:
                if not i & 1:
                    ans.append(lst.pop(0))
                else:
                    lst.append(lst.pop(0))
                i += 1
            return ans
        
        n = len(deck)
        order = reveal(n)
        lst_of_lists = [[v, i] for i, v in enumerate(order)]
        lst_of_lists.sort(key=lambda x: x[0])
        sorted_deck = sorted(deck)
        return [sorted_deck[i] for _, i in lst_of_lists]