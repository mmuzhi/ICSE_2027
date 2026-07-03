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
        while st and sr:
            st.pop()
            sr.pop()
        return not st