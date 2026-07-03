class Solution:
    def checkValidString(self, s):
        st = []
        sr = []
        n = len(s)
        for i in range(n): 
            if s[i] == '(':
                st.append(i)
            elif s[i] == '*':
                sr.append(i)
            else:
                if st:
                    st.pop()
                elif sr:
                    sr.pop()
                else:
                    return False
        j = 0
        for i in range(len(st)):
            while j < len(sr) and sr[j] <= st[i]:
                j += 1
            if j >= len(sr):
                return False
            j += 1
        return True