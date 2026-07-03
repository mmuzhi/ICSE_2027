class AvgPartition:

    def __init__(self, lst, limit):
        self.lst = lst.copy()
        self.limit = limit

    def setNum(self):
        n = len(self.lst)
        if self.limit == 0:
            raise ZeroDivisionError('Limit cannot be zero')
        size = n // self.limit
        remainder = n % self.limit
        return (size, remainder)

    def get(self, index):
        size, remainder = self.setNum()
        start = index * size + min(index, remainder)
        end = start + size
        if index + 1 <= remainder:
            end += 1
        return self.lst[start:end]