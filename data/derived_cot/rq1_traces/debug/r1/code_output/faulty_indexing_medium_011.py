import collections

class Solution:
    def invalidTransactions(self, transactions: List[str]) -> List[str]:
        invalid = []
        txn = collections.defaultdict(list)
        
        for trn in transactions:
            name, time, amount, city = trn.split(",")
            txn[name].append([time, amount, city])
        
        for trn_str in transactions:
            name, time, amount, city = trn_str.split(",")
            if int(amount) > 1000:
                invalid.append(trn_str)
            else:
                for other in txn[name]:
                    time_i, _, city_i = other
                    if city != city_i and abs(int(time) - int(time_i)) <= 60:
                        invalid.append(trn_str)
                        break

        return invalid