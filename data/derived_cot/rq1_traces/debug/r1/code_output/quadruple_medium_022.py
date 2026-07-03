class Solution:
    def smallestString(self, s: str) -> str:
        check = set(s)
        if len(check) == 1:
            if check == {'a'}:
                return s[:-1] + 'z' if s else 'z'
            else:
                return ''.join(chr(ord(c) - 1) for c in s)
        
        ct1 = 0
        while ct1 < len(s) and s[ct1] == 'a':
            ct1 += 1
        ans = 'a' * ct1
        s = s[ct1:]
        
        change = False
        ct2 = 0
        contiguous = True
        for cha in s:
            ct2 += 1
            if cha != 'a':
                ans += chr(ord(cha) - 1)
                change = True
            else:
                ans += cha
                if change:
                    contiguous = False
                    break
            if not contiguous:
                break
        
        return ans + s[ct2:] if change else (ans[:-1] + 'z' if ans else 'z')