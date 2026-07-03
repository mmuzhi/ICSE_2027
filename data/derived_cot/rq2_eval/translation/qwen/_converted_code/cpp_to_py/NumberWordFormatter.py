class NumberWordFormatter:

    def __init__(self):
        self.NUMBER = ['', 'ONE', 'TWO', 'THREE', 'FOUR', 'FIVE', 'SIX', 'SEVEN', 'EIGHT', 'NINE']
        self.NUMBER_TEEN = ['TEN', 'ELEVEN', 'TWELVE', 'THIRTEEN', 'FOURTEEN', 'FIFTEEN', 'SIXTEEN', 'SEVENTEEN', 'EIGHTEEN', 'NINETEEN']
        self.NUMBER_TEN = ['TEN', 'TWENTY', 'THIRTY', 'FORTY', 'FIFTY', 'SIXTY', 'SEVENTY', 'EIGHTY', 'NINETY']
        self.NUMBER_MORE = ['', 'THOUSAND', 'MILLION', 'BILLION']

    def format(self, x):
        if x is None:
            return self.format_string(None)
        elif isinstance(x, (int, float)):
            x_str = str(x)
            return self.format_string(x_str)
        else:
            return self.format_string(x)

    def format_string(self, x):
        if x is None:
            return ''
        if isinstance(x, str):
            if '.' in x:
                parts = x.split('.', 1)
                lstr = parts[0]
                rstr = parts[1]
            else:
                lstr = x
                rstr = ''
            if lstr == '':
                lstr = '0'
            lstr_reversed = lstr[::-1]
            if len(lstr_reversed) % 3 == 1:
                lstr_reversed += '00'
            elif len(lstr_reversed) % 3 == 2:
                lstr_reversed += '0'
            num_chunks = len(lstr_reversed) // 3
            lm = ''
            for i in range(num_chunks):
                start = i * 3
                end = start + 3
                chunk = lstr_reversed[start:end]
                if chunk == '000':
                    continue
                chunk_words = self.trans_three(chunk)
                scale = self.parse_more(i)
                if lm == '':
                    lm = chunk_words + ' ' + scale
                else:
                    lm = chunk_words + ' ' + scale + ' ' + lm
            if lm != '':
                lm = lm.rstrip()
            xs = ''
            if rstr != '':
                xs = 'AND CENTS ' + self.trans_two(rstr) + ' '
            if xs != '':
                xs = xs.rstrip()
            if lm == '':
                return 'ZERO ONLY'
            else:
                return lm + ' ' + xs + 'ONLY'
        else:
            return self.format_string(str(x))

    def trans_two(self, s):
        if len(s) == 1:
            s = '0' + s
        if s[0] == '0':
            return self.NUMBER[int(s[1])]
        elif s[0] == '1':
            return self.NUMBER_TEEN[int(s[1])]
        elif s[1] == '0':
            return self.NUMBER_TEN[int(s[0]) - 1]
        else:
            return self.NUMBER_TEN[int(s[0]) - 1] + ' ' + self.NUMBER[int(s[1])]

    def trans_three(self, s):
        if s[0] == '0':
            return self.trans_two(s[1:])
        elif s[1:] == '00':
            return self.NUMBER[int(s[0])] + ' HUNDRED'
        else:
            return self.NUMBER[int(s[0])] + ' HUNDRED AND ' + self.trans_two(s[1:])

    def parse_more(self, i):
        return self.NUMBER_MORE[i]