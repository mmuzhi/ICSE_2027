class AvgPartition:
    class ViewList:
        def __init__(self, lst, start, end):
            self.lst = lst
            self.start = start
            self.end = end
        
        def __len__(self):
            return self.end - self.start
        
        def __getitem__(self, index):
            if isinstance(index, slice):
                start, stop, step = index.indices(len(self))
                return self.lst[self.start + start:self.start + stop:step]
            if isinstance(index, int):
                if index < 0:
                    index += len(self)
                if index < 0 or index >= len(self):
                    raise IndexError("list index out of range")
                return self.lst[self.start + index]
            raise TypeError("Index must be integer or slice")
        
        def __setitem__(self, index, value):
            if isinstance(index, slice):
                s = index
                start, stop, step = s.indices(len(self))
                for i in range(start, stop, step):
                    self.lst[self.start + i] = value[i - start]
            elif isinstance(index, int):
                if index < 0:
                    index += len(self)
                if index < 0 or index >= len(self):
                    raise IndexError("list index out of range")
                self.lst[self.start + index] = value
        
        def __repr__(self):
            return repr(self.lst[self.start:self.end])
    
    def __init__(self, lst, limit):
        self.lst = lst
        self.limit = limit
    
    def setNum(self):
        size = len(self.lst) // self.limit
        remainder = len(self.lst) % self.limit
        return (size, remainder)
    
    def get(self, index):
        size, remainder = self.setNum()
        start = index * size + min(index, remainder)
        end = start + size
        if index + 1 <= remainder:
            end += 1
        return AvgPartition.ViewList(self.lst, start, end)

# Example usage:
if __name__ == "__main__":
    lst = [1, 2, 3, 4, 5, 6, 7]
    a = AvgPartition(lst, 3)
    print(a.get(0))  # Output: [1, 2, 3, 4] (if remainder is 1, but in this case, 7//3=2, remainder=1)
    # Note: The actual output depends on the list size and limit.