class NumberWordFormatter:
    def __init__(self):
        self.NUMBER = ["", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"]
        self.NUMBER_TEEN = ["TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"]
        self.NUMBER_TEN = ["TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"]
        self.NUMBER_MORE = ["", "THOUSAND", "MILLION", "BILLION"]

    def format(self, x):
        if x is None:
            return ""
        elif isinstance(x, (int, float)):
            return self.format(str(x))
        elif isinstance(x, str):
            return self._format_string(x)
        else:
            raise TypeError("Unsupported type for formatting")

    def _format_string(self, s):
        if '.' in s:
            parts = s.split('.')
            lstr = parts[0]
            rstr = parts[1]
        else:
            lstr = s
            rstr = ""

        lstr_reversed = lstr[::-1]

        if len(lstr_reversed) % 3 == 1:
            lstr_reversed += "00"
        elif len(lstr_reversed) % 3 == 2:
            lstr_reversed += "0"

        groups = []
        for i in range(0, len(lstr_reversed), 3):
            groups.append(lstr_reversed[i:i+3])

        lm = ""
        for idx, group in enumerate(groups):
            if group == "000":
                continue
            num_str = self._trans_three(group)
            if num_str:
                suffix = self._parse_more(idx)
                if suffix:
                    num_str += f" {suffix}"
                if lm:
                    num_str += f" {lm}"
                lm = num_str

        xs = "AND CENTS " + self._trans_two(rstr) + " " if rstr else ""
        if not lm:
            return "ZERO ONLY"
        lm_stripped = lm.rstrip()
        return f"{lm_stripped} {xs}ONLY"

    def _trans_two(self, s):
        if len(s) == 1:
            s = "0" + s
        if s[0] == '0':
            return self.NUMBER[int(s[1])]
        elif s[0] == '1':
            return self.NUMBER_TEEN[int(s) - 10]
        elif s[1] == '0':
            return self.NUMBER_TEN[int(s[0]) - 1]
        else:
            return f"{self.NUMBER_TEN[int(s[0]) - 1]} {self.NUMBER[int(s[1])]"

    def _trans_three(self, s):
        if s[0] == '0':
            return self._trans_two(s[1:])
        elif s[1:] == "00":
            return f"{self.NUMBER[int(s[0])]} HUNDRED"
        else:
            return f"{self.NUMBER[int(s[0])]} HUNDRED AND {self._trans_two(s[1:])}"

    def _parse_more(self, i):
        return self.NUMBER_MORE[i]

# Example usage:
# formatter = NumberWordFormatter()
# print(formatter.format(123.45))  # Output: ONE HUNDRED AND TWENTY THREE THOUSAND AND CENTS FORTY FIVE ONLY