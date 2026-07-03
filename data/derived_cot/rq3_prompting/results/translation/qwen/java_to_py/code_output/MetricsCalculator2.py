class Tuple:
    def __init__(self, list, totalNum):
        self.list = list
        self.totalNum = totalNum

def mrr(data):
    if isinstance(data, Tuple):
        if data.totalNum == 0:
            return 0.0
        for i, val in enumerate(data.list):
            if val == 1:
                return 1.0 / (i + 1)
        return 0.0
    elif isinstance(data, (list, tuple)):
        results = []
        for t in data:
            if not isinstance(t, Tuple):
                raise ValueError("Input must be a Tuple or a list/tuple of Tuples")
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
    else:
        raise ValueError("Input must be a Tuple or a list/tuple of Tuples")

def map(data):
    if isinstance(data, Tuple):
        if data.totalNum == 0:
            return 0.0
        ap = 0.0
        count = 0
        for i, val in enumerate(data.list):
            if val == 1:
                count += 1
                ap += count / (i + 1.0)
        return ap / data.totalNum
    elif isinstance(data, (list, tuple)):
        results = []
        for t in data:
            if not isinstance(t, Tuple):
                raise ValueError("Input must be a Tuple or a list/tuple of Tuples")
            if t.totalNum == 0:
                results.append(0.0)
            else:
                ap = 0.0
                count = 0
                for i, val in enumerate(t.list):
                    if val == 1:
                        count += 1
                        ap += count / (i + 1.0)
                results.append(ap / t.totalNum)
        if not results:
            return 0.0
        return sum(results) / len(results)
    else:
        raise ValueError("Input must be a Tuple or a list/tuple of Tuples")