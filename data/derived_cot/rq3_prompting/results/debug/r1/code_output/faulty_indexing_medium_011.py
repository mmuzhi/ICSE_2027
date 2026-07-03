from typing import List
import collections

class Solution:
    def invalidTransactions(self, transactions: List[str]) -> List[str]:
        invalid = []
        txn = collections.defaultdict(list)
        
        for trn in transactions:
            name, time, amount, city = trn.split(",")
            txn[name].append([time, amount, city])
        
        for trn in transactions:
            name, time, amount, city = trn.split(",")
            if int(amount) > 1000:
                invalid.append(trn)
            else:
                for time_i, _, city_i in txn[name]:
                    if city != city_i and abs(int(time) - int(time_i)) <= 60:
                        invalid.append(trn)
                        break
        
        return invalid