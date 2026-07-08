class AvgPartition:
    def __init__(self, lst, limit):
        self.lst = lst
        self.limit = limit

    def setNum(self):
        size = len(self.lst) // self.limit
        remainder = len(self.lst) % self.limit
        return [size, remainder]

    def get(self, index):
        nums = self.setNum()
        size = nums[0]
        remainder = nums[1]
        start = index * size + min(index, remainder)
        end = start + size
        if index + 1 <= remainder:
            end += 1
        
        # Replicate Java's subList boundary exceptions
        if start < 0 or end > len(self.lst):
            raise IndexError("Index out of bounds")
        
        return self.lst[start:end]


if __name__ == "__main__":
    lst = [1, 2, 3, 4]
    a = AvgPartition(lst, 2)
    print(a.get(0))
    print(a.get(1))