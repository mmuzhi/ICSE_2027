class Solution:
    def invalidTransactions(self, transactions: List[str]) -> List[str]:
        invalid = []
        txn_dict = {}
        for trn in transactions:
            parts = trn.split(',')
            name = parts[0]
            time = parts[1]
            amount = parts[2]
            city = parts[3]
            if name not in txn_dict:
                txn_dict[name] = []
            txn_dict[name].append((time, city))
        
        for i, trn in enumerate(transactions):
            parts = trn.split(',')
            name = parts[0]
            time_str = parts[1]
            amount = parts[2]
            city = parts[3]
            if int(amount) > 1000:
                invalid.append(trn)
            else:
                if name in txn_dict:
                    other_transactions = txn_dict[name].copy()
                    try:
                        other_transactions.remove((time_str, city))
                    except ValueError:
                        pass
                    current_time = int(time_str)
                    for t, c in other_transactions:
                        t_int = int(t)
                        if c != city and abs(current_time - t_int) <= 60:
                            invalid.append(trn)
                            break
        return invalid