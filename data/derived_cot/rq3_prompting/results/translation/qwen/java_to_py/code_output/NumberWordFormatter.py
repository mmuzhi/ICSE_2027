class NumberWordFormatter:
    def __init__(self):
        self.NUMBER = ["", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"]
        self.NUMBER_TEEN = ["TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"]
        self.NUMBER_TEN = ["TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"]
        self.NUMBER_MORE = ["", "THOUSAND", "MILLION", "BILLION"]

    def format(self, x):
        if x is None:
            return ""
        return self.format_string(str(x))

    def format_string(self, x):
        parts = x.split('.')
        lstr = parts[0]
        rstr = parts[1] if len(parts) > 1 else ""
        
        if lstr.strip() == '':
            if rstr == '':
                return "ZERO ONLY"
            else:
                return "ZERO ONLY"
                
        lstr_rev = lstr[::-1]
        if len(lstr_rev) % 3 == 1:
            lstr_rev += '00'
        elif len(lstr_rev) % 3 == 2:
            lstr_rev += '0'
            
        chunks = [lstr_rev[i:i+3] for i in range(0, len(lstr_rev), 3)]
        left_parts = []
        
        for i, chunk in enumerate(chunks):
            reversed_chunk = chunk[::-1]
            if reversed_chunk == "000":
                left_parts.insert(0, "")
            else:
                word_part = self.trans_three(reversed_chunk)
                scale_word = self.parse_more(i)
                left_parts.insert(0, word_part + " " + scale_word + " ")
                
        left_str = " ".join(left_parts).strip()
        if left_str == "":
            left_str = "ZERO"
            
        if rstr != "":
            cents_part = "AND CENTS " + self.trans_two(rstr) + " "
        else:
            cents_part = ""
            
        return left_str + " " + cents_part + "ONLY"

    def trans_two(self, s):
        s = s.zfill(2)
        if s[0] == '0':
            return self.NUMBER[int(s[1])]
        elif s[0] == '1':
            return self.NUMBER_TEEN[int(s) - 10]
        else:
            if s[1] == '0':
                return self.NUMBER_TEN[int(s[0])-1]
            else:
                return self.NUMBER_TEN[int(s[0])-1] + " " + self.NUMBER[int(s[1])]

    def trans_three(self, s):
        if s[0] == '0':
            return self.trans_two(s[1:])
        elif s[1:] == "00":
            return self.NUMBER[int(s[0])] + " HUNDRED"
        else:
            return self.NUMBER[int(s[0])] + " HUNDRED AND " + self.trans_two(s[1:])

    def parse_more(self, i):
        return self.NUMBER_MORE[i]