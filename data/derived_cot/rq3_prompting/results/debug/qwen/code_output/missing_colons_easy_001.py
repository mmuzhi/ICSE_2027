class Solution:
    def areAlmostEqual(self, s1: str, s2: str) -> bool:
        if len(s1) != len(s2):
            return False
        if s1 == s2:
            return True
        diff = []
        for i in range(len(s1)):
            if s1[i] != s2[i]:
                diff.append([s1[i], s2[i]])
        if len(diff) == 2:
            if diff[0] == diff[1][::-1]:
                return True
            else:
                return False
        elif len(diff) == 4:
            if sorted(s1) != sorted(s2):
                return False
            def is_reverse(d1, d2):
                return d1 == d2[::-1]
            if is_reverse(diff[0], diff[1]) and is_reverse(diff[2], diff[3]):
                return True
            if is_reverse(diff[0], diff[2]) and is_reverse(diff[1], diff[3]):
                return True
            if is_reverse(diff[0], diff[3]) and is_reverse(diff[1], diff[2]):
                return True
            return False
        else:
            return False