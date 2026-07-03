class NumberWordFormatter:
    def __init__(self):
        self.NUMBER = ["", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"]
        self.NUMBER_TEEN = ["TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"]
        self.NUMBER_TEN = ["TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"]
        self.NUMBER_MORE = ["", "THOUSAND", "MILLION", "BILLION"]
        self.NUMBER_SUFFIX = ["k", "w", "", "m", "", "", "b", "", "", "t", "", "", "p", "", "", "e"]
    
    def format(self, x):
        if x is None:
            return self.format_null()
        elif isinstance(x, int):
            return self.format_int(x)
        elif isinstance(x, float):
            return self.format_double(x)
        elif isinstance(x, str):
            return self.format_string(x)
        else:
            raise TypeError("Unsupported type")
    
    def format_int(self, x):
        return self.format_string(str(x))
    
    def format_double(self, x):
        return self.format_string(str(x))
    
    def format_string(self, x):
        if '.' in x:
            parts = x.split('.', 1)
            lstr = parts[0]
            rstr = parts[1]
        else:
            lstr = x
            rstr = ""
        
        lstr = lstr[::-1]
        
        n = len(lstr)
        if n % 3 == 1:
            lstr += "00"
        elif n % 3 == 2:
            lstr += "0"
        
        num_chunks = len(lstr) // 3
        lm = ""
        
        for i in range(num_chunks):
            start_index = 3 * i
            chunk = lstr[start_index:start_index+3]
            chunk = chunk[::-1]
            
            if chunk != "000":
                word = self.trans_three(chunk)
                more = self.parse_more(i)
                segment = word
                if more:
                    segment += " " + more
                if lm:
                    lm = segment + " " + lm
                else:
                    lm = segment
        
        if lm:
            idx = len(lm) - 1
            while idx >= 0 and lm[idx] == ' ':
                idx -= 1
            lm = lm[:idx+1]
        
        xs = ""
        if rstr:
            cents = self.trans_two(rstr)
            xs = "AND CENTS " + cents + " "
        
        if not lm:
            return "ZERO ONLY"
        else:
            return lm + " " + xs + "ONLY"
    
    def format_null(self):
        return ""
    
    def trans_two(self, s):
        ss = s
        if len(ss) == 1:
            ss = "0" + ss
        
        if ss[0] == '0':
            return self.NUMBER[int(ss[1])]
        elif ss[0] == '1':
            num_val = int(ss)
            idx = num_val - 10
            return self.NUMBER_TEEN[idx]
        elif ss[1] == '0':
            idx = int(ss[0]) - 1
            return self.NUMBER_TEN[idx]
        else:
            part1 = self.NUMBER_TEN[int(ss[0]) - 1]
            part2 = self.NUMBER[int(ss[1])]
            return part1 + " " + part2
    
    def trans_three(self, s):
        if s[0] == '0':
            return self.trans_two(s[1:])
        elif s[1:] == "00":
            return self.NUMBER[int(s[0])] + " HUNDRED"
        else:
            return self.NUMBER[int(s[0])] + " HUNDRED AND " + self.trans_two(s[1:])
    
    def parse_more(self, i):
        return self.NUMBER_MORE[i]