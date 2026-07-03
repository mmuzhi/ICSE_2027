class Solution:
    def largestInteger(self, num: int) -> int:
        if num == 0:
            return 0
        nums = [int(x) for x in str(num)]
        evenlist = []
        oddlist = []
        for i in nums:
            if i % 2 == 0:
                evenlist.append(i)
            else:
                oddlist.append(i)
        evenlist.sort()
        oddlist.sort(reverse=True)
        i, j = 0, 0
        res = []
        while i < len(evenlist) or j < len(oddlist):
            if i < len(evenlist) and j < len(oddlist):
                if evenlist[i] >= oddlist[j]:
                    res.append(str(evenlist[i]))
                    i += 1
                else:
                    res.append(str(oddlist[j]))
                    j += 1
            elif i < len(evenlist):
                res.append(str(evenlist[i]))
                i += 1
            else:
                res.append(str(oddlist[j]))
                j += 1
        return int(''.join(res))