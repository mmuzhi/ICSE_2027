class Solution:
    def pivotArray(self, nums: List[int], pivot: int) -> List[int]:
        lst = []      # for numbers less than pivot
        val = []      # for numbers equal to pivot
        tmp = []      # for numbers greater than pivot
        for i in nums:
            if i == pivot:
                val.append(i)
            elif i < pivot:
                lst.append(i)
            else:
                tmp.append(i)
        return lst + val + tmp