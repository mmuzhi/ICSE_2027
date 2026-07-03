class Solution:
    def checkValidString(self, s):
        st = []
        sr = []
        for i in range(len(s)):
            if s[i]=='(':
                st.append(i)
            elif s[i]== '*':
                sr.append(i)
            else:
                if st:
                    st.pop()
                elif sr:
                    sr.pop()
                else:
                    return False
        i = 0
        j = 0
        while i < len(st) and j < len(sr):
            if st[i] < sr[j]:
                i += 1
            else:
                j += 1
        return i == len(st)