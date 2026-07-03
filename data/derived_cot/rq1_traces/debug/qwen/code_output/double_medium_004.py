from collections import defaultdict

class Solution:
    def findWinners(self, matches: List[List[int]]) -> List[List[int]]:
        losses_count = defaultdict(int)
        players = set()
        
        for match in matches:
            loser = match[1]
            losses_count[loser] += 1
            players.add(match[0])
            players.add(loser)
        
        list1 = []
        list2 = []
        
        for player in players:
            count = losses_count.get(player, 0)
            if count == 0:
                list1.append(player)
            elif count == 1:
                list2.append(player)
        
        list1.sort()
        list2.sort()
        
        return [list1, list2]