class Tuple:
    def __init__(self, lst, total_num):
        self.list = lst
        self.totalNum = total_num

def mrr(data):
    if not isinstance(data, Tuple) and not isinstance(data, list):
        raise ValueError("the input must be a tuple([0,...,1,...],int) or a list of tuples")
    
    if isinstance(data, Tuple):
        lst = data.list
        total_num = data.totalNum
        
        if total_num == 0:
            return 0.0
        
        for i, val in enumerate(lst):
            if val == 1:
                return 1.0 / (i + 1)
        return 0.0
    else:
        results = []
        for t in data:
            if t.totalNum == 0:
                results.append(0.0)
            else:
                for i, val in enumerate(t.list):
                    if val == 1:
                        results.append(1.0 / (i + 1))
                        break
                else:
                    results.append(0.0)
        
        if not results:
            return 0.0
        return sum(results) / len(results)

def map(data):
    if not isinstance(data, Tuple) and not isinstance(data, list):
        raise ValueError("the input must be a tuple([0,...,1,...],int) or a list of tuples")
    
    if isinstance(data, Tuple):
        lst = data.list
        total_num = data.totalNum
        
        if total_num == 0:
            return 0.0
        
        count = 0
        ap = 0.0
        for i, val in enumerate(lst):
            if val == 1:
                count += 1
                ap += count / (i + 1.0)
        return ap / total_num
    else:
        results = []
        for t in data:
            if t.totalNum == 0:
                results.append(0.0)
            else:
                count = 0
                ap = 0.0
                for i, val in enumerate(t.list):
                    if val == 1:
                        count += 1
                        ap += count / (i + 1.0)
                results.append(ap / t.totalNum)
        
        if not results:
            return 0.0
        return sum(results) / len(results)