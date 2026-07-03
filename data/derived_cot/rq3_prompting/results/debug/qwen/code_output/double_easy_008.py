class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        s = ''.join(map(str, digits))
        num = int(s) + 1
        return [int(x) for x in str(num)]