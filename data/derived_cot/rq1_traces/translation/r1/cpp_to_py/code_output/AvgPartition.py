class AvgPartition:
    def __init__(self, lst, limit):
        self.lst = lst
        self.limit = limit
    
    def set_num(self):
        n = len(self.lst)
        size = n // self.limit
        remainder = n % self.limit
        return size, remainder
    
    def get(self, index):
        size, remainder = self.set_num()
        start = index * size + min(index, remainder)
        end = start + size
        if index < remainder:
            end += 1
        return self.lst[start:end]