import collections

class Solution:
    def invalidTransactions(self, transactions: List[str]) -> List[str]:
        invalid = []
        txn = {}
        
        for idx, trans in enumerate(transactions):
            parts = trans.split(',')
            name = parts[0]
            time = int(parts[1])
            city = parts[3]
            if name not in txn:
                txn[name] = []
            txn[name].append((time, city, idx))
        
        for idx, trans in enumerate(transactions):
            parts = trans.split(',')
            name = parts[0]
            time = int(parts[1])
            amount = int(parts[2])
            city = parts[3]
            
            if amount > 1000:
                invalid.append(trans)
            else:
                found = False
                for t, c, i in txn[name]:
                    if i == idx:
                        continue
                    if c != city and abs(time - t) <= 60:
                        found = True
                        break
                if found:
                    invalid.append(trans)
        
        return invalid