class NumberWordFormatter:
    NUMBER = ["", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"]
    NUMBER_TEEN = ["TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"]
    NUMBER_TEN = ["TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"]
    NUMBER_MORE = ["", "THOUSAND", "MILLION", "BILLION"]
    NUMBER_SUFFIX = ["k", "w", "", "m", "", "", "b", "", "", "t", "", "", "p", "", "", "e"]

    def format(self, x):
        if x is None:
            return ""
        if isinstance(x, int):
            return self._format_str(str(x))
        if isinstance(x, float):
            return self._format_str(str(x))
        if isinstance(x, str):
            return self._format_str(x)
        raise TypeError("Unsupported type")

    def _format_str(self, x):
        # Split integer and fractional parts
        dot_pos = x.find('.')
        if dot_pos == -1:
            lstr = x
            rstr = ""
        else:
            lstr = x[:dot_pos]
            rstr = x[dot_pos + 1:]

        # Reverse integer part
        lstr = lstr[::-1]

        # Pad to multiple of 3
        if len(lstr) % 3 == 1:
            lstr += "00"
        elif len(lstr) % 3 == 2:
            lstr += "0"

        a = [""] * 5
        lm = ""
        for i in range(len(lstr) // 3):
            # Extract group of three in original order
            a[i] = lstr[3 * i + 2] + lstr[3 * i + 1] + lstr[3 * i]
            if a[i] != "000":
                lm = self.trans_three(a[i]) + " " + self.parse_more(i) + " " + lm
            else:
                lm += self.trans_three(a[i])  # empty string for "000"

        # Cents part
        if rstr:
            xs = "AND CENTS " + self.trans_two(rstr) + " "
        else:
            xs = ""

        if not lm:
            return "ZERO ONLY"
        else:
            # Remove trailing spaces
            end = len(lm) - 1
            while end >= 0 and lm[end] == ' ':
                end -= 1
            lm = lm[:end + 1]
            return lm + " " + xs + "ONLY"

    def trans_two(self, s):
        if len(s) == 1:
            s = "0" + s
        if s[0] == '0':
            return self.NUMBER[int(s[1])]
        elif s[0] == '1':
            return self.NUMBER_TEEN[int(s) - 10]
        elif s[1] == '0':
            return self.NUMBER_TEN[int(s[0]) - 1]
        else:
            return self.NUMBER_TEN[int(s[0]) - 1] + " " + self.NUMBER[int(s[1])]

    def trans_three(self, s):
        if s[0] == '0':
            return self.trans_two(s[1:])
        elif s[1:] == "00":
            return self.NUMBER[int(s[0])] + " HUNDRED"
        else:
            return self.NUMBER[int(s[0])] + " HUNDRED AND " + self.trans_two(s[1:])

    def parse_more(self, i):
        return self.NUMBER_MORE[i]