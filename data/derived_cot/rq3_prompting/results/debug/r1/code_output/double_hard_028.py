class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not set(s2).issubset(set(s1)):
            return 0
        s1 = ''.join(c for c in s1 if c in set(s2))

        repeatCount = [0] * (n1 + 1)
        nextIndex = [0] * (n1 + 1)
        index = 0
        count = 0

        for i in range(1, n1 + 1):
            for ch in s1:
                if ch == s2[index]:
                    index += 1
                    if index == len(s2):
                        index = 0
                        count += 1
            repeatCount[i] = count
            nextIndex[i] = index

            for j in range(i):
                if nextIndex[j] == index:
                    prevCount = repeatCount[j]
                    patternCount = repeatCount[i] - prevCount
                    patternLen = i - j
                    remaining = n1 - j
                    patternTimes = remaining // patternLen
                    totalCount = prevCount + patternCount * patternTimes
                    remainingRest = remaining % patternLen
                    totalCount += repeatCount[j + remainingRest] - repeatCount[j]
                    return totalCount // n2

        return repeatCount[n1] // n2