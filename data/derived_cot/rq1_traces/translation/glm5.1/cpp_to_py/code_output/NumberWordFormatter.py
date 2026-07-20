from functools import singledispatchmethod


class NumberWordFormatter:
    def __init__(self):
        self.NUMBER = ["", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"]
        self.NUMBER_TEEN = ["TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN",
                            "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"]
        self.NUMBER_TEN = ["TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"]
        self.NUMBER_MORE = ["", "THOUSAND", "MILLION", "BILLION"]
        # NUMBER_SUFFIX is present in the C++ class but never used; kept for consistency
        self.NUMBER_SUFFIX = ["k", "w", "", "m", "", "", "b", "", "", "t", "", "", "p", "", "", "e"]

    @singledispatchmethod
    def format(self, x):
        raise NotImplementedError("Unsupported type")

    @format.register(int)
    def _format_int(self, x):
        return self.format(str(x))

    @format.register(float)
    def _format_float(self, x):
        # Emulate std::stringstream default formatting for double (equivalent to %.6g)
        return self.format('{:.6g}'.format(x))

    @format.register(str)
    def _format_str(self, x: str):
        # Split into integer part and fractional part
        dot_pos = x.find('.')
        if dot_pos != -1:
            lstr = x[:dot_pos]
            rstr = x[dot_pos + 1:]
        else:
            lstr = x
            rstr = ""

        lstr = lstr[::-1]  # reverse

        # Pad to multiple of 3
        rem = len(lstr) % 3
        if rem == 1:
            lstr += "00"
        elif rem == 2:
            lstr += "0"

        a = [""] * 5
        lm = ""

        for i in range(len(lstr) // 3):
            # Reconstruct the original 3-digit group from the reversed string
            a[i] = lstr[3 * i + 2] + lstr[3 * i + 1] + lstr[3 * i]
            if a[i] != "000":
                lm = self.trans_three(a[i]) + " " + self.parse_more(i) + " " + lm
            else:
                lm += self.trans_three(a[i])

        xs = "AND CENTS " + self.trans_two(rstr) + " " if rstr else ""

        if not lm:
            return "ZERO ONLY"
        else:
            # Trim trailing spaces
            nowpos = 0
            for i in range(len(lm) - 1, -1, -1):
                if lm[i] != ' ':
                    nowpos = i
                    break
            lm = lm[:nowpos + 1]
            return lm + " " + xs + "ONLY"

    @format.register(type(None))
    def _format_none(self, x):
        return ""

    def trans_two(self, s: str):
        ss = s
        if len(ss) == 1:
            ss = "0" + ss

        if ss[0] == '0':
            return self.NUMBER[ord(ss[1]) - ord('0')]
        elif ss[0] == '1':
            return self.NUMBER_TEEN[int(ss) - 10]
        elif ss[1] == '0':
            return self.NUMBER_TEN[ord(ss[0]) - ord('1')]
        else:
            return self.NUMBER_TEN[ord(ss[0]) - ord('1')] + " " + self.NUMBER[ord(ss[1]) - ord('0')]

    def trans_three(self, s: str):
        if s[0] == '0':
            return self.trans_two(s[1:])
        elif s[1:] == "00":
            return self.NUMBER[ord(s[0]) - ord('0')] + " HUNDRED"
        else:
            return self.NUMBER[ord(s[0]) - ord('0')] + " HUNDRED AND " + self.trans_two(s[1:])

    def parse_more(self, i: int):
        return self.NUMBER_MORE[i]